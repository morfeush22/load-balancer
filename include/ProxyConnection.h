//
// Created by morfeush22 on 04.03.19.
//

#ifndef LOAD_BALANCER_PROXYCONNECTION_H
#define LOAD_BALANCER_PROXYCONNECTION_H

#include "ServersRepository.h"
#include <boost/asio.hpp>


class ProxyConnection {

    public:
    explicit ProxyConnection(boost::asio::io_context &io_context, std::shared_ptr<ServersRepository> servers_repository, std::string backend_cookie_name);
    boost::asio::ip::tcp::socket & FrontendSocket();
    void run();

    private:
    boost::asio::ip::tcp::socket frontend_socket_;
    std::shared_ptr<ServersRepository> servers_repository_;
    std::string backend_cookie_name_;
};


#endif //LOAD_BALANCER_PROXYCONNECTION_H
