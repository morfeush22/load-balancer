//
// Created by morfeush22 on 05.03.19.
//

#ifndef LOAD_BALANCER_PROXYCONNECTIONFACTORY_H
#define LOAD_BALANCER_PROXYCONNECTIONFACTORY_H

#include "../include/ProxyConnection.h"
#include <boost/asio.hpp>


class ProxyConnectionFactory {

    public:
    explicit ProxyConnectionFactory(boost::asio::io_context &io_context);
    std::shared_ptr<ProxyConnection> MakeProxyConnection();

    private:
    boost::asio::io_context &_io_context;

};


#endif //LOAD_BALANCER_PROXYCONNECTIONFACTORY_H
