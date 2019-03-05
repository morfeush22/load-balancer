//
// Created by morfeush22 on 04.03.19.
//

#include "../include/ProxyConnection.h"

namespace beast = boost::beast;
namespace http = beast::http;
namespace asio = boost::asio;
using namespace std;
using tcp = boost::asio::ip::tcp;


ProxyConnection::ProxyConnection(boost::asio::io_context &io_context, std::shared_ptr<ServersRepository> servers_repository, std::string backend_cookie_name):
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
    auto server = servers_repository_->GetAllServers().front();
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

    // Send the response
    //handle_request(*doc_root_, std::move(req_), lambda_);
    std::cout << request_ << "\n";
    do_close();
}

void ProxyConnection::do_close() {
    beast::error_code ec;
    frontend_socket_.shutdown(tcp::socket::shutdown_send, ec);

    // At this point the connection is closed gracefully
}
