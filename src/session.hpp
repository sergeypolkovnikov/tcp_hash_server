#pragma once
#include <boost/asio.hpp>
#include "hasher.hpp"

struct Session : std::enable_shared_from_this<Session> {
    Session(boost::asio::ip::tcp::socket socket);
    void start();

private:
    void do_read();

    boost::asio::ip::tcp::socket socket;
    Hasher hasher;
    std::array<char, 4096> buffer;
};