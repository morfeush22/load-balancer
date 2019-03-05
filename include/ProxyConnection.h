//
// Created by morfeush22 on 04.03.19.
//

#ifndef LOAD_BALANCER_PROXYCONNECTION_H
#define LOAD_BALANCER_PROXYCONNECTION_H

#include "ServersRepository.h"
#include <boost/asio.hpp>


class ProxyConnection: public std::enable_shared_from_this<ProxyConnection> {

    public:
    explicit ProxyConnection(boost::asio::io_context &io_context, std::shared_ptr<ServersRepository> servers_repository, std::string backend_cookie_name);
    boost::asio::ip::tcp::socket & FrontendSocket();
    void run();

    private:
    boost::asio::ip::tcp::resolver resolver_;
    boost::asio::ip::tcp::socket frontend_socket_;
    boost::asio::ip::tcp::socket backend_socket_;
    boost::beast::flat_buffer buffer_;
    boost::beast::http::request<boost::beast::http::string_body > request_;
    boost::beast::http::response<boost::beast::http::string_body> response_;

    std::shared_ptr<ServersRepository> servers_repository_;
    std::string backend_cookie_name_;

    void on_read(boost::beast::error_code error_code, std::size_t bytes_transferred);
    void do_close();
};


#endif //LOAD_BALANCER_PROXYCONNECTION_H
