//
// Created by morfeush22 on 04.03.19.
//

#ifndef LOAD_BALANCER_SERVER_H
#define LOAD_BALANCER_SERVER_H

#include "../include/ConfigParser.h"
#include "../include/ProxyConnectionFactory.h"
#include <boost/asio.hpp>
#include <boost/beast/core/error.hpp>


class FrontendServer: public std::enable_shared_from_this<FrontendServer> {

    public:
    FrontendServer(boost::asio::io_context &io_context, std::shared_ptr<ConfigParser> config_parser, std::unique_ptr<ProxyConnectionFactory> proxy_connection_factory);
    void run();

    private:
    boost::asio::io_context & io_context_;
    std::unique_ptr<ProxyConnectionFactory> proxy_connection_factory_;
    boost::asio::ip::tcp::acceptor acceptor_;
    boost::asio::ip::tcp::endpoint endpoint_;

    void do_accept();
    void on_accept(std::shared_ptr<ProxyConnection> proxy_connection, boost::beast::error_code error_code);
};


#endif //LOAD_BALANCER_SERVER_H
