//
// Created by morfeush22 on 04.03.19.
//

#ifndef LOAD_BALANCER_SERVER_H
#define LOAD_BALANCER_SERVER_H

#include "ConfigParser.h"
#include "ProxyConnectionFactory.h"
#include <boost/asio.hpp>
#include <boost/beast/core/error.hpp>


class FrontendServer : public std::enable_shared_from_this<FrontendServer> {

public:
    /**
     * Listens to incoming connections and passes them to one of healthy backend servers.
     * @param io_context Reference to Boost io_context object
     * @param proxy_connection_factory Pointer to ProxyConnectionFactory class instance
     * @param config_parser Pointer to ConfigParser class instance
     */
    FrontendServer(boost::asio::io_context &io_context,
                   std::unique_ptr<ProxyConnectionFactory> proxy_connection_factory,
                   std::shared_ptr<ConfigParser> config_parser);

    void run();

private:
    boost::asio::ip::tcp::acceptor acceptor_;
    boost::asio::ip::tcp::endpoint endpoint_;
    boost::asio::io_context &io_context_;
    std::unique_ptr<ProxyConnectionFactory> proxy_connection_factory_;

    void do_accept();

    void on_accept(std::shared_ptr<ProxyConnection> proxy_connection, boost::beast::error_code error_code);
};


#endif //LOAD_BALANCER_SERVER_H
