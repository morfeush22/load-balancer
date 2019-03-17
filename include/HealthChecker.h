//
// Created by morfeush22 on 28.02.19.
//

#ifndef LOAD_BALANCER_HEALTHCHECKER_H
#define LOAD_BALANCER_HEALTHCHECKER_H

#include "ConfigParser.h"
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast.hpp>
#include <boost/beast/http.hpp>


class HealthChecker : public std::enable_shared_from_this<HealthChecker> {

public:
    /**
     * Takes care of ensuring that given backend server correctly responds to HTTP requests.
     * @param io_context Reference to Boost io_context object
     * @param health_check_endpoint HTTP path that is used to check backend server healthiness, must respond with 200 code
     * @param health_check_period Interval of HTTP health check requests
     */
    HealthChecker(boost::asio::io_context &io_context, std::string health_check_endpoint,
                      unsigned int health_check_period);

    /**
     * Starts health checking process.
     * @param host Address of backend server
     * @param port Listen port of backend server
     */
    void run(std::string host, std::string port);

    /**
     * Returns backend server health status.
     * @return True if backend server is healthy, false otherwise
     */
    bool Healthy();

private:
    boost::beast::flat_buffer buffer_;
    boost::asio::deadline_timer deadline_timer_;
    std::atomic<bool> healthy_ = false;
    std::string health_check_endpoint_;
    unsigned int health_check_period_;
    boost::beast::http::request<boost::beast::http::empty_body> request_;
    boost::asio::ip::tcp::resolver resolver_;
    boost::beast::http::response<boost::beast::http::string_body> response_;
    boost::asio::ip::tcp::socket socket_;

    void on_resolve(boost::beast::error_code error_code, boost::asio::ip::tcp::resolver::iterator endpoint_iterator);

    void on_connect(boost::beast::error_code error_code, boost::asio::ip::tcp::resolver::iterator endpoint_iterator);

    void on_write(boost::beast::error_code error_code, std::size_t bytes_transferred);

    void on_read(boost::beast::error_code error_code, std::size_t bytes_transferred);

};


#endif //LOAD_BALANCER_HEALTHCHECKER_H
