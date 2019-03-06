//
// Created by morfeush22 on 04.03.19.
//

#include "../include/ProxyConnection.h"

namespace beast = boost::beast;
namespace http = beast::http;
namespace asio = boost::asio;
using namespace std;
using tcp = boost::asio::ip::tcp;


ProxyConnection::ProxyConnection(boost::asio::io_context &io_context, std::shared_ptr<BackendServersRepository> servers_repository, std::string backend_cookie_name):
resolver_(io_context),
frontend_socket_(io_context),
backend_socket_(io_context),
servers_repository_(move(servers_repository)),
backend_cookie_name_(move(backend_cookie_name))
{}

boost::asio::ip::tcp::socket & ProxyConnection::FrontendSocket() {
    return frontend_socket_;
}

void ProxyConnection::run() {
    request_ = {};

    http::async_read(
            frontend_socket_,
            buffer_,
            request_,
            boost::bind(
                    &ProxyConnection::on_read,
                    shared_from_this(),
                    asio::placeholders::error,
                    asio::placeholders::bytes_transferred
            )
    );

    std::cout << "run\n";
}

void ProxyConnection::on_read(boost::beast::error_code error_code, std::size_t bytes_transferred) {
    boost::ignore_unused(bytes_transferred);

    // This means they closed the connection
    if(error_code == http::error::end_of_stream) {
        return do_close();
    }

    if(error_code) {
        std::cout << "fail\n";
        return;
    }

    server_request_ = request_;

    //start connection to server
    auto server = servers_repository_->GetAllServers().front();
    //request_.set(http::field::host, host);

    resolver_.async_resolve(
            server.address,
            server.port,
            boost::bind(
                    &ProxyConnection::on_resolve,
                    shared_from_this(),
                    asio::placeholders::error,
                    asio::placeholders::iterator
            )
    );

    // Send the response
    //handle_request(*doc_root_, std::move(req_), lambda_);
    //std::cout << request_ << "\n";
    //do_close();
}

void ProxyConnection::do_close() {
    beast::error_code ec;
    frontend_socket_.shutdown(tcp::socket::shutdown_send, ec);

    // At this point the connection is closed gracefully
}

void ProxyConnection::on_resolve(boost::beast::error_code error_code,
                                 boost::asio::ip::tcp::resolver::iterator endpoint_iterator) {
    if (! error_code) {
        tcp::endpoint endpoint = *endpoint_iterator;
        backend_socket_.async_connect(
                endpoint,
                boost::bind(
                        &ProxyConnection::on_server_connect,
                        shared_from_this(),
                        asio::placeholders::error,
                        ++endpoint_iterator
                )
        );
    }
}

void ProxyConnection::on_server_connect(boost::beast::error_code error_code,
                                        boost::asio::ip::tcp::resolver::iterator endpoint_iterator) {
    if (! error_code) {
        http::async_write(
                backend_socket_,
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
        backend_socket_.close();
        tcp::endpoint endpoint = *endpoint_iterator;
        backend_socket_.async_connect(
                endpoint,
                boost::bind(
                        &ProxyConnection::on_server_connect,
                        shared_from_this(),
                        asio::placeholders::error,
                        ++endpoint_iterator
                )
        );
    }

}

void ProxyConnection::on_server_write(boost::beast::error_code error_code, std::size_t bytes_transferred) {
    boost::ignore_unused(bytes_transferred);

    if (! error_code) {
        http::async_read(
                backend_socket_,
                server_buffer_,
                server_response_,
                boost::bind(
                        &ProxyConnection::on_server_read,
                        shared_from_this(),
                        asio::placeholders::error,
                        asio::placeholders::bytes_transferred
                )
        );
    }
}

void ProxyConnection::on_server_read(boost::beast::error_code error_code, std::size_t bytes_transferred) {
    boost::ignore_unused(bytes_transferred);

    if (! error_code) {
        backend_socket_.shutdown(tcp::socket::shutdown_both, error_code);

        response_ = server_response_;

        http::async_write(
                frontend_socket_,
                response_,
                boost::bind(
                        &ProxyConnection::on_write,
                        shared_from_this(),
                        asio::placeholders::error,
                        asio::placeholders::bytes_transferred
                )
        );
    }
}

void ProxyConnection::on_write(boost::beast::error_code error_code, std::size_t bytes_transferred) {
    boost::ignore_unused(bytes_transferred);

    if (! error_code) {
        do_close();
    }
}
