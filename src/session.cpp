#include "session.hpp"
#include <iostream>

Session::Session(boost::asio::ip::tcp::socket socket)
    : socket{ std::move(socket) } {
}

void Session::start() {
    std::cout << "Session::start" << std::endl;
    do_read();
}

namespace {
    void print_chunk(std::span<const char> chunk) {
        for (char c : chunk) {
            std::cout << c << " ";
        }
        std::cout << "end of chunk " << std::endl;
    }

    template<typename F>
    void process_chunk(std::span<char> read_buf, Hasher& hasher, F&& reply) {
        std::cout << "process_chunk" << read_buf.size() << std::endl;
        while (!read_buf.empty()) {
            const auto pos = std::ranges::find(read_buf, '\n');
            if (pos != read_buf.end()) {
                hasher.add_chunk(read_buf.subspan(0, std::distance(read_buf.begin(), pos)));
                const auto hash = hash_to_str(hasher.finilize());
                reply(hash);
                read_buf = std::span{ pos + 1, read_buf.end() };
                std::cout << "process_chunk finish" << read_buf.size() << std::endl;
                continue;
            }
            else {
                hasher.add_chunk(read_buf);
                std::cout << "process_chunk wo enter " << read_buf.size() << std::endl;
                print_chunk(read_buf);
                break;
            }
        }
    }

}

void Session::do_read() {
    std::cout << "Session::do_read" << std::endl;
    auto self = shared_from_this();
    socket.async_read_some(boost::asio::buffer(buffer),
        [this, self](const boost::system::error_code ec, const std::size_t length) {
            if (!ec) {
                process_chunk(std::span{ buffer.begin(), length }, hasher, [&](const std::string& hash) { boost::system::error_code ignored_ec; boost::asio::write(socket, boost::asio::buffer(hash), ignored_ec); });
                do_read();
            }
            else {
                std::cout << "socket.async_read_some failed " << ec << std::endl;
            }
        });
}
