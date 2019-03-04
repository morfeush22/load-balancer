//
// Created by morfeush22 on 28.02.19.
//

#include "../include/HealthChecker.h"

#define HTTP_VERSION 10

namespace beast = boost::beast;
namespace http = beast::http;
namespace asio = boost::asio;
using namespace std;
using tcp = boost::asio::ip::tcp;


HealthChecker::HealthChecker(boost::asio::io_context &io_context, unsigned int health_check_period, string health_check_endpoint):
deadline_timer_(io_context),
resolver_(io_context),
socket_(io_context)
{
    _health_check_period = health_check_period;
    _health_check_endpoint = move(health_check_endpoint);
}

void HealthChecker::run(std::string host, std::string port) {
    request_.method(http::verb::get);
    request_.set(http::field::host, host);
    request_.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    request_.target(_health_check_endpoint);
    request_.version(HTTP_VERSION);

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


    deadline_timer_.expires_from_now(boost::posix_time::seconds(_health_check_period));
    deadline_timer_.async_wait(
            boost::bind(
                    &HealthChecker::run,
                    shared_from_this(),
                    host,
                    port
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
    else {
        healthy_ = false;
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
    else {
        healthy_ = false;
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
    else {
        healthy_ = false;
    }
}

void HealthChecker::on_read(beast::error_code error_code, std::size_t bytes_transferred) {
    boost::ignore_unused(bytes_transferred);

    if (! error_code) {
        healthy_ = response_.result() == beast::http::status::ok;
        socket_.shutdown(tcp::socket::shutdown_both, error_code);
    }
    else {
        healthy_ = false;
    }
}

bool HealthChecker::healthy() {
    return healthy_;
}
