//
// Created by morfeush22 on 04.03.19.
//

#include "../include/ProxyConnection.h"

ProxyConnection::ProxyConnection(boost::asio::io_context &io_context, std::shared_ptr<ServersRepository> servers_repository, std::string backend_cookie_name):
frontend_socket_(io_context),
servers_repository_(move(servers_repository)),
backend_cookie_name_(move(backend_cookie_name))
{}

boost::asio::ip::tcp::socket & ProxyConnection::FrontendSocket() {
    return frontend_socket_;
}

void ProxyConnection::run() {
    std::cout << "run\n";
}
