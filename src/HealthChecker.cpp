//
// Created by morfeush22 on 28.02.19.
//

#include "../include/HealthChecker.h"
#include "../include/Logger.h"

#define HTTP_VERSION 10

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace http = beast::http;
using namespace std;
using tcp = boost::asio::ip::tcp;


HealthChecker::HealthChecker(boost::asio::io_context &io_context, string health_check_endpoint,
                             unsigned int health_check_period) :
        deadline_timer_(io_context),
        health_check_endpoint_(move(health_check_endpoint)),
        health_check_period_(health_check_period),
        resolver_(io_context),
        socket_(io_context) {
}

void HealthChecker::run(string host, string port) {
    request_.method(http::verb::get);
    request_.set(http::field::host, host);
    request_.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    request_.target(health_check_endpoint_);
    request_.version(HTTP_VERSION);

    if (!healthy_) {
        WARNING("backend server is NOT healthy: ", host, ":", port, health_check_endpoint_);
    } else {
        DEBUG("backend server is responding: ", host, ":", port, health_check_endpoint_);
    }

    DEBUG("sending health check to backend server: ", host, ":", port, health_check_endpoint_);

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


    deadline_timer_.expires_from_now(boost::posix_time::seconds(health_check_period_));
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
    if (!error_code) {
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
    } else {
        healthy_ = false;
    }
}

void HealthChecker::on_connect(beast::error_code error_code, tcp::resolver::iterator endpoint_iterator) {
    if (!error_code) {
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
    } else if (endpoint_iterator != tcp::resolver::iterator()) {
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
    } else {
        healthy_ = false;
    }
}

void HealthChecker::on_write(beast::error_code error_code, size_t bytes_transferred) {
    boost::ignore_unused(bytes_transferred);

    if (!error_code) {
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
    } else {
        healthy_ = false;
    }
}

void HealthChecker::on_read(beast::error_code error_code, size_t bytes_transferred) {
    boost::ignore_unused(bytes_transferred);

    if (!error_code) {
        healthy_ = response_.result() == beast::http::status::ok;
        socket_.shutdown(tcp::socket::shutdown_both, error_code);
    } else {
        healthy_ = false;
    }
}

bool HealthChecker::healthy() {
    return healthy_;
}
