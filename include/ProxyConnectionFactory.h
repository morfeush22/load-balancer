//
// Created by morfeush22 on 05.03.19.
//

#ifndef LOAD_BALANCER_PROXYCONNECTIONFACTORY_H
#define LOAD_BALANCER_PROXYCONNECTIONFACTORY_H

#include "ProxyConnection.h"
#include "BackendServersRepository.h"
#include "SchedulingStrategy.h"
#include <boost/asio.hpp>


class ProxyConnectionFactory {

    public:
    ProxyConnectionFactory(boost::asio::io_context &io_context,
            std::shared_ptr<ConfigParser> config_parser,
            std::shared_ptr<BackendServersRepository>,
            const SchedulingStrategy &scheduling_strategy);
    std::shared_ptr<ProxyConnection> MakeProxyConnection();

    private:
    boost::asio::io_context &_io_context;
    std::shared_ptr<ConfigParser> config_parser_;
    std::shared_ptr<BackendServersRepository> servers_repository_;
    const SchedulingStrategy &scheduling_strategy_;
};


#endif //LOAD_BALANCER_PROXYCONNECTIONFACTORY_H
