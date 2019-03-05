//
// Created by morfeush22 on 04.03.19.
//

#include "../include/ProxyConnection.h"

ProxyConnection::ProxyConnection(boost::asio::io_context &io_context):
frontend_socket_(io_context)
{}

boost::asio::ip::tcp::socket & ProxyConnection::FrontendSocket() {
    return frontend_socket_;
}
