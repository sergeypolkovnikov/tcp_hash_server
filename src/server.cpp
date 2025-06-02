#include "server.hpp"
#include "session.hpp"
#include <iostream>

Server::Server(boost::asio::io_context& io_context, const unsigned short port)
    : acceptor(io_context, boost::asio::ip::tcp::endpoint{ boost::asio::ip::tcp::v4(), port })
    , socket{ io_context } {
    do_accept();
}

void Server::do_accept() {
    std::cout << "Server::do_accept()" << std::endl;
    acceptor.async_accept(socket, 
        [this](boost::system::error_code ec) {
            if (!ec) {
                std::make_shared<Session>(std::move(socket))->start();
            }
            else {
                std::cout << "Accept failed: " << ec.message() << std::endl;
            }
            socket = boost::asio::ip::tcp::socket(acceptor.get_executor());
            do_accept();
        });
}
