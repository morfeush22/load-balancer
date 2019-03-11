//
// Created by morfeush22 on 05.03.19.
//

#ifndef LOAD_BALANCER_PROXYCONNECTIONFACTORY_H
#define LOAD_BALANCER_PROXYCONNECTIONFACTORY_H

#include "BackendServersRepository.h"
#include "ProxyConnection.h"
#include "SchedulingStrategy.h"
#include <boost/asio.hpp>


class ProxyConnectionFactory {

public:
    ProxyConnectionFactory(boost::asio::io_context &io_context,
                           std::shared_ptr<BackendServersRepository> backend_servers_repository,
                           std::shared_ptr<SchedulingStrategy> scheduling_strategy,
                           std::shared_ptr<ConfigParser> config_parser);

    std::shared_ptr<ProxyConnection> MakeProxyConnection();

private:
    bool backend_insert_cookie_;
    std::string backend_cookie_name_;
    boost::asio::io_context &io_context_;
    std::shared_ptr<BackendServersRepository> servers_repository_;
    std::shared_ptr<SchedulingStrategy> scheduling_strategy_;
};


#endif //LOAD_BALANCER_PROXYCONNECTIONFACTORY_H
