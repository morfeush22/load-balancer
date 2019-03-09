//
// Created by morfeush22 on 04.03.19.
//

#include "../include/Logger.h"
#include "../include/ProxyConnection.h"
#include <boost/lexical_cast.hpp>

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace http = beast::http;
using namespace std;
using tcp = boost::asio::ip::tcp;


ProxyConnection::ProxyConnection(boost::asio::io_context &io_context,
                                 std::shared_ptr<BackendServersRepository> backend_servers_repository,
                                 std::shared_ptr<SchedulingStrategy> scheduling_strategy) :
resolver_(io_context),
client_socket_(io_context),
server_socket_(io_context),
backend_servers_repository_(move(backend_servers_repository)),
scheduling_strategy_(move(scheduling_strategy))
{}

boost::asio::ip::tcp::socket &ProxyConnection::FrontendSocket() {
    return client_socket_;
}

void ProxyConnection::run() {
    client_request_ = {};

    http::async_read(
            client_socket_,
            client_buffer_,
            client_request_,
            boost::bind(
                    &ProxyConnection::on_client_read,
                    shared_from_this(),
                    asio::placeholders::error,
                    asio::placeholders::bytes_transferred
            )
    );

    DEBUG("new connection from: ", boost::lexical_cast<std::string>(client_socket_.remote_endpoint()));
}

void ProxyConnection::on_client_read(boost::beast::error_code error_code, std::size_t bytes_transferred) {
    boost::ignore_unused(bytes_transferred);

    if(error_code == http::error::end_of_stream) {
        return do_close();
    }

    if(error_code) {
        ERROR("on_client_read: ", error_code);
        return;
    }

    auto servers_list = backend_servers_repository_->GetAllServers();
    if (servers_list.empty()) {
        WARNING("no feasible backend servers to route connection");
        return do_close();
    }

    server_request_ = client_request_;
    backend_server_description_ = scheduling_strategy_->SelectBackendServer(server_request_, servers_list);

    resolver_.async_resolve(
            backend_server_description_.address,
            backend_server_description_.port,
            boost::bind(
                    &ProxyConnection::on_server_resolve,
                    shared_from_this(),
                    asio::placeholders::error,
                    asio::placeholders::iterator
            )
    );
}

void ProxyConnection::do_close() {
    beast::error_code ec;
    client_socket_.shutdown(tcp::socket::shutdown_send, ec);
}

void ProxyConnection::on_server_resolve(boost::beast::error_code error_code,
                                        boost::asio::ip::tcp::resolver::iterator endpoint_iterator) {
    if (! error_code) {
        tcp::endpoint endpoint = *endpoint_iterator;

        server_socket_.async_connect(
                endpoint,
                boost::bind(
                        &ProxyConnection::on_server_connect,
                        shared_from_this(),
                        asio::placeholders::error,
                        ++endpoint_iterator
                )
        );
    } else {
        ERROR("on_server_resolve: ", error_code);
    }
}

void ProxyConnection::on_server_connect(boost::beast::error_code error_code,
                                        boost::asio::ip::tcp::resolver::iterator endpoint_iterator) {
    if (! error_code) {
        http::async_write(
                server_socket_,
                server_request_,
                boost::bind(
                        &ProxyConnection::on_server_write,
                        shared_from_this(),
                        asio::placeholders::error,
                        asio::placeholders::bytes_transferred
                )
        );
    }
    else if (endpoint_iterator != tcp::resolver::iterator()) {
        server_socket_.close();
        tcp::endpoint endpoint = *endpoint_iterator;

        server_socket_.async_connect(
                endpoint,
                boost::bind(
                        &ProxyConnection::on_server_connect,
                        shared_from_this(),
                        asio::placeholders::error,
                        ++endpoint_iterator
                )
        );
    } else {
        ERROR("on_server_connect: ", error_code);
    }

}

void ProxyConnection::on_server_write(boost::beast::error_code error_code, std::size_t bytes_transferred) {
    boost::ignore_unused(bytes_transferred);

    if (! error_code) {
        http::async_read(
                server_socket_,
                server_buffer_,
                server_response_,
                boost::bind(
                        &ProxyConnection::on_server_read,
                        shared_from_this(),
                        asio::placeholders::error,
                        asio::placeholders::bytes_transferred
                )
        );
    } else {
        ERROR("on_server_write: ", error_code);
    }
}

void ProxyConnection::on_server_read(boost::beast::error_code error_code, std::size_t bytes_transferred) {
    boost::ignore_unused(bytes_transferred);

    if (! error_code) {
        server_socket_.shutdown(tcp::socket::shutdown_both, error_code);
        client_response_ = server_response_;

        http::async_write(
                client_socket_,
                client_response_,
                boost::bind(
                        &ProxyConnection::on_client_write,
                        shared_from_this(),
                        asio::placeholders::error,
                        asio::placeholders::bytes_transferred
                )
        );
    } else {
        ERROR("on_server_read: ", error_code);
    }
}

void ProxyConnection::on_client_write(boost::beast::error_code error_code, std::size_t bytes_transferred) {
    boost::ignore_unused(bytes_transferred);

    if (! error_code) {
        do_close();
    } else {
        ERROR("on_client_write: ", error_code);
    }
}
