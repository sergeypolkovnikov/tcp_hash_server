#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <mutex>
#include <sstream>
#include <iomanip>
#include <unistd.h>
#include <span>
#include <algorithm>
#include <csignal>
#include <netinet/in.h>
#include "hasher.hpp"

template<typename F>
void process_chunk(std::stop_token st, std::span<char> read_buf, Hasher& hasher, F&& reply) {
    while (!read_buf.empty() && !st.stop_requested()) {
        const auto pos = std::ranges::find(read_buf, '\n');
        if (pos != read_buf.end()) {
            hasher.add_chunk(read_buf.subspan(0, std::distance(read_buf.begin(), pos)));
            const auto hash = hash_to_str(hasher.finilize());
            reply(hash);
            read_buf = std::span{ pos + 1, read_buf.end() };
            continue;
        }
        else {
            hasher.add_chunk(read_buf);
            break;
        }
    }
}

void handle_client(std::stop_token st,  const int client_fd) {
    constexpr size_t BUFFER_SIZE = 4096;
    std::array<char, BUFFER_SIZE> buffer; 
    Hasher hasher;
    while (!st.stop_requested()) {
        const auto read_bytes = read(client_fd, buffer.data(), buffer.size());
        if (read_bytes <= 0) {
            break;
        }
        std::span read_buf{ buffer.begin(), read_bytes};
        process_chunk(st, read_buf, hasher, [client_fd](const std::string& hash) { write(client_fd, hash.data(), hash.size()); });
    }
    close(client_fd);
}

struct Server {
    Server(const int port): port { port } {}

    void start() {
        server_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (server_fd == -1) {
            perror("socket");
            return;
        }

        const int opt = 1;
        setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

        sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = INADDR_ANY;
        addr.sin_port = htons(port);

        if (bind(server_fd, (sockaddr*)&addr, sizeof(addr)) < 0) {
            perror("bind");
            return;
        }

        if (listen(server_fd, SOMAXCONN) < 0) {
            perror("listen");
            return;
        }

        std::cout << "Server listening on port " << port << "\n";

        alive = true;
        while (alive) {
            int client_fd = accept(server_fd, nullptr, nullptr);
            if (client_fd < 0) {
                perror("accept");
                continue;
            }
            connections.push_back(std::jthread(handle_client, client_fd));
        }
    }

    void stop() {
        alive = false;
        close(server_fd);
        connections.clear();
    }

private:
    bool alive = true;
    int port;
    int server_fd;
    std::vector<std::jthread> connections;
};

constexpr int PORT = 9000;
Server server{ PORT };

void handle_sigint(int signal) {
    std::cout << "\nCaught SIGINT (Ctrl+C). Exiting...\n";
    server.stop();
}

int main() {
    std::signal(SIGINT, handle_sigint);
    server.start();
    return 0;
}