//
// Created by morfeush22 on 04.03.19.
//

#include "../include/FrontendServer.h"
#include "../include/Logger.h"
#include <boost/lexical_cast.hpp>

namespace asio = boost::asio;


FrontendServer::FrontendServer(boost::asio::io_context &io_context, std::shared_ptr<ConfigParser> config_parser,
                               std::unique_ptr<ProxyConnectionFactory> proxy_connection_factory) :
        io_context_(io_context),
        acceptor_(io_context),
        endpoint_(asio::ip::make_address_v4(config_parser->FrontendAddress()),
                  boost::lexical_cast<unsigned short>(config_parser->FrontendPort())),
        proxy_connection_factory_(move(proxy_connection_factory)) {
    boost::beast::error_code error_code;

    acceptor_.open(endpoint_.protocol(), error_code);
    if (error_code) {
        ERROR("can not open endpoint: ", error_code);
        return;
    }

    acceptor_.set_option(asio::socket_base::reuse_address(true), error_code);
    if (error_code) {
        ERROR("can not set socket options: ", error_code);
        return;
    }

    acceptor_.bind(endpoint_, error_code);
    if (error_code) {
        ERROR("can not bind on endpoint: ", error_code);
        return;
    }

    acceptor_.listen(
            asio::socket_base::max_listen_connections, error_code);
    if (error_code) {
        ERROR("can not accept connections on socket: ", error_code);
        return;
    }

}

void FrontendServer::run() {
    if (!acceptor_.is_open()) {
        WARNING("socket is not open");
        return;
    }
    do_accept();
}

void FrontendServer::do_accept() {
    auto proxy_connection = proxy_connection_factory_->MakeProxyConnection();

    acceptor_.async_accept(
            proxy_connection->FrontendSocket(),
            boost::bind(
                    &FrontendServer::on_accept,
                    shared_from_this(),
                    proxy_connection,
                    asio::placeholders::error
            )
    );

}

void FrontendServer::on_accept(std::shared_ptr<ProxyConnection> proxy_connection, boost::beast::error_code error_code) {
    if (!error_code) {
        proxy_connection->run();
        do_accept();
    } else {
        WARNING("can not accept connection");
    }
}
