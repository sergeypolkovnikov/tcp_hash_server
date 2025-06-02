#include <boost/asio.hpp>
#include <csignal>
#include <thread>
#include <iostream>

#include "server.hpp"

int main() {
    std::cout << "main" << std::endl;
    boost::asio::io_context io_context;
    std::vector<std::jthread> threads;

    try {
        Server server(io_context, 9000);

        for (int i = 0; i < std::thread::hardware_concurrency(); ++i) {
            threads.emplace_back([&io_context]() {
                io_context.run();
                });
        }
    }
    catch(const std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}