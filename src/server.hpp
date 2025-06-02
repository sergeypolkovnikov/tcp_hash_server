#pragma once
#include <boost/asio.hpp>

struct Server {
    Server(boost::asio::io_context& io_context, const unsigned short port);

private:
    void do_accept();

    boost::asio::ip::tcp::acceptor acceptor;
    boost::asio::ip::tcp::socket socket;
};