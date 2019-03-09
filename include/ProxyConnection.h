//
// Created by morfeush22 on 04.03.19.
//

#ifndef LOAD_BALANCER_PROXYCONNECTION_H
#define LOAD_BALANCER_PROXYCONNECTION_H

#include "BackendServersRepository.h"
#include "SchedulingStrategy.h"
#include <boost/asio.hpp>


class ProxyConnection : public std::enable_shared_from_this<ProxyConnection> {

public:
    ProxyConnection(boost::asio::io_context &io_context,
                        std::shared_ptr<BackendServersRepository> backend_servers_repository,
                        std::shared_ptr<SchedulingStrategy> scheduling_strategy);

    boost::asio::ip::tcp::socket &FrontendSocket();

    void run();

private:
    BackendServerDescription backend_server_description_;
    std::shared_ptr<BackendServersRepository> backend_servers_repository_;
    boost::beast::flat_buffer client_buffer_;
    boost::beast::http::request<boost::beast::http::string_body> client_request_;
    boost::beast::http::response<boost::beast::http::string_body> client_response_;
    boost::asio::ip::tcp::socket client_socket_;
    boost::asio::ip::tcp::resolver resolver_;
    boost::beast::flat_buffer server_buffer_;
    boost::beast::http::request<boost::beast::http::string_body> server_request_;
    boost::beast::http::response<boost::beast::http::string_body> server_response_;
    boost::asio::ip::tcp::socket server_socket_;
    std::shared_ptr<SchedulingStrategy> scheduling_strategy_;

    void on_client_read(boost::beast::error_code error_code, std::size_t bytes_transferred);

    void on_client_write(boost::beast::error_code error_code, std::size_t bytes_transferred);

    void on_server_resolve(
            boost::beast::error_code error_code,
            boost::asio::ip::tcp::resolver::iterator endpoint_iterator);

    void on_server_connect(
            boost::beast::error_code error_code,
            boost::asio::ip::tcp::resolver::iterator endpoint_iterator);

    void on_server_read(boost::beast::error_code error_code, std::size_t bytes_transferred);

    void on_server_write(boost::beast::error_code error_code, std::size_t bytes_transferred);

    void do_close();
};


#endif //LOAD_BALANCER_PROXYCONNECTION_H
