//
// Created by morfeush22 on 04.03.19.
//

#ifndef LOAD_BALANCER_PROXYCONNECTION_H
#define LOAD_BALANCER_PROXYCONNECTION_H

#include "BackendServersRepository.h"
#include "SchedulingStrategy.h"
#include <boost/asio.hpp>


class ProxyConnection: public std::enable_shared_from_this<ProxyConnection> {

    public:
    ProxyConnection(boost::asio::io_context &io_context,
            std::shared_ptr<BackendServersRepository> servers_repository,
            std::shared_ptr<SchedulingStrategy> scheduling_strategy,
            std::string backend_cookie_name);
    boost::asio::ip::tcp::socket & FrontendSocket();
    void run();

    private:
    boost::asio::ip::tcp::resolver resolver_;
    boost::asio::ip::tcp::socket frontend_socket_;
    boost::asio::ip::tcp::socket backend_socket_;
    boost::beast::flat_buffer buffer_;
    boost::beast::flat_buffer server_buffer_;
    boost::beast::http::request<boost::beast::http::string_body > request_;
    boost::beast::http::request<boost::beast::http::string_body > server_request_;
    boost::beast::http::response<boost::beast::http::string_body> response_;
    boost::beast::http::response<boost::beast::http::string_body> server_response_;

    std::shared_ptr<BackendServersRepository> servers_repository_;
    std::shared_ptr<SchedulingStrategy> scheduling_strategy_;
    std::string backend_cookie_name_;
    BackendServerDescription backend_server_;

    void on_read(boost::beast::error_code error_code, std::size_t bytes_transferred);
    void on_resolve(boost::beast::error_code error_code, boost::asio::ip::tcp::resolver::iterator endpoint_iterator);
    void on_server_connect(boost::beast::error_code error_code, boost::asio::ip::tcp::resolver::iterator endpoint_iterator);
    void on_server_write(boost::beast::error_code error_code, std::size_t bytes_transferred);
    void on_server_read(boost::beast::error_code error_code, std::size_t bytes_transferred);
    void on_write(boost::beast::error_code error_code, std::size_t bytes_transferred);
    void do_close();
};


#endif //LOAD_BALANCER_PROXYCONNECTION_H
