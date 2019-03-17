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
    /**
     * Takes care of constructing valid ProxyConnection objects.
     * @param io_context io_context Reference to Boost io_context object
     * @param backend_servers_repository Pointer to BackendServersRepository class instance
     * @param scheduling_strategy Pointer to SchedulingStrategy class instance
     * @param config_parser Pointer to ConfigParser class instance
     */
    ProxyConnectionFactory(boost::asio::io_context &io_context,
                           std::shared_ptr<BackendServersRepository> backend_servers_repository,
                           std::shared_ptr<SchedulingStrategy> scheduling_strategy,
                           std::shared_ptr<ConfigParser> config_parser);

    /**
     * Constructs new ProxyConnection object.
     * @return Newly constructed ProxyConnection object
     */
    std::shared_ptr<ProxyConnection> MakeProxyConnection();

private:
    bool backend_insert_cookie_;
    std::string backend_cookie_name_;
    boost::asio::io_context &io_context_;
    std::shared_ptr<BackendServersRepository> servers_repository_;
    std::shared_ptr<SchedulingStrategy> scheduling_strategy_;
};


#endif //LOAD_BALANCER_PROXYCONNECTIONFACTORY_H
