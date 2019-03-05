//
// Created by morfeush22 on 04.03.19.
//

#include <boost/lexical_cast.hpp>
#include "../include/LoadBalancer.h"

namespace asio = boost::asio;


LoadBalancer::LoadBalancer(boost::asio::io_context & io_context, std::shared_ptr<ConfigParser> config_parser, std::unique_ptr<ProxyConnectionFactory> proxy_connection_factory):
_io_context(io_context),
acceptor_(io_context),
endpoint_(asio::ip::make_address_v4(config_parser->FrontendAdress()), boost::lexical_cast< unsigned short>(config_parser->FrontendPort())),
proxy_connection_factory_(move(proxy_connection_factory))
{
    boost::beast::error_code ec;

    acceptor_.open(endpoint_.protocol(), ec);
    if(ec)
    {
//        fail(ec, "open");
        return;
    }

    acceptor_.set_option(asio::socket_base::reuse_address(true), ec);
    if(ec)
    {
//        fail(ec, "set_option");
        return;
    }

    acceptor_.bind(endpoint_, ec);
    if(ec)
    {
//        fail(ec, "bind");
        return;
    }

    // Start listening for connections
    acceptor_.listen(
            asio::socket_base::max_listen_connections, ec);
    if(ec)
    {
//        fail(ec, "listen");
        return;
    }

}

void LoadBalancer::run() {
    if(! acceptor_.is_open())
        return;
    do_accept();
}

void LoadBalancer::do_accept() {
    auto proxy_connection = proxy_connection_factory_->MakeProxyConnection();

    acceptor_.async_accept(
            proxy_connection->FrontendSocket(),
            boost::bind(
                    &LoadBalancer::on_accept,
                    shared_from_this(),
                    proxy_connection,
                    asio::placeholders::error
                    )
    );

}

void LoadBalancer::on_accept(std::shared_ptr<ProxyConnection> proxy_connection, boost::beast::error_code error_code) {

}
