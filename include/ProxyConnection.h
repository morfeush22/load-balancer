//
// Created by morfeush22 on 04.03.19.
//

#ifndef LOAD_BALANCER_PROXYCONNECTION_H
#define LOAD_BALANCER_PROXYCONNECTION_H

#include <boost/asio.hpp>


class ProxyConnection {

    public:
    explicit ProxyConnection(boost::asio::io_context &io_context);
    boost::asio::ip::tcp::socket & FrontendSocket();

    private:
    boost::asio::ip::tcp::socket frontend_socket_;
};


#endif //LOAD_BALANCER_PROXYCONNECTION_H
