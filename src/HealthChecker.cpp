//
// Created by morfeush22 on 28.02.19.
//

#include "../include/HealthChecker.h"

#define HTTP_VERSION 10

namespace beast = boost::beast;
namespace http = beast::http;
namespace asio = boost::asio;
using tcp = boost::asio::ip::tcp;


HealthChecker::HealthChecker(boost::asio::io_context &io_context, std::shared_ptr<ConfigParser> config_parser):
resolver_(io_context),
socket_(io_context)
{}

void HealthChecker::run(std::string host, std::string port, std::string path) {
    request_.version(HTTP_VERSION);
    request_.method(http::verb::get);
    request_.target(path);
    request_.set(http::field::host, host);
    request_.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

    resolver_.async_resolve(
            host,
            port,
            boost::bind(
                    &HealthChecker::on_resolve,
                    shared_from_this(),
                    asio::placeholders::error,
                    asio::placeholders::iterator
                    )
            );
}

void HealthChecker::on_resolve(beast::error_code error_code, tcp::resolver::iterator endpoint_iterator) {
    if (! error_code) {
        tcp::endpoint endpoint = *endpoint_iterator;
        socket_.async_connect(
                endpoint,
                boost::bind(
                        &HealthChecker::on_connect,
                        shared_from_this(),
                        asio::placeholders::error,
                        ++endpoint_iterator
                        )
                );
    }
}

void HealthChecker::on_connect(beast::error_code error_code, tcp::resolver::iterator endpoint_iterator) {
    if (! error_code) {
        http::async_write(
                socket_,
                request_,
                boost::bind(
                        &HealthChecker::on_write,
                        shared_from_this(),
                        asio::placeholders::error,
                        asio::placeholders::bytes_transferred
                        )
                );
    }
    else if (endpoint_iterator != tcp::resolver::iterator()) {
        socket_.close();
        tcp::endpoint endpoint = *endpoint_iterator;
        socket_.async_connect(
                endpoint,
                boost::bind(
                        &HealthChecker::on_connect,
                        shared_from_this(),
                        asio::placeholders::error,
                        ++endpoint_iterator
                )
        );
    }
}

void HealthChecker::on_write(beast::error_code error_code, std::size_t bytes_transferred) {
    boost::ignore_unused(bytes_transferred);

    if (! error_code) {
        http::async_read(
                socket_,
                buffer_,
                response_,
                boost::bind(
                        &HealthChecker::on_read,
                        shared_from_this(),
                        asio::placeholders::error,
                        asio::placeholders::bytes_transferred
                        )
                );
    }

}

void HealthChecker::on_read(beast::error_code error_code, std::size_t bytes_transferred) {
    boost::ignore_unused(bytes_transferred);

    if (! error_code) {
        std::cout << response_ << "\n";

        socket_.shutdown(tcp::socket::shutdown_both, error_code);
    }

}
