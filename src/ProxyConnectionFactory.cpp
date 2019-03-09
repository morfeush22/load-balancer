//
// Created by morfeush22 on 05.03.19.
//

#include "../include/ProxyConnectionFactory.h"
#include <curses.h>

using namespace std;


ProxyConnectionFactory::ProxyConnectionFactory(boost::asio::io_context &io_context,
                                               shared_ptr<BackendServersRepository> backend_servers_repository,
                                               shared_ptr<SchedulingStrategy> scheduling_strategy) :
        io_context_(io_context),
        servers_repository_(move(backend_servers_repository)),
        scheduling_strategy_(move(scheduling_strategy)) {}

shared_ptr<ProxyConnection> ProxyConnectionFactory::MakeProxyConnection() {
    return make_shared<ProxyConnection>(io_context_, servers_repository_, scheduling_strategy_);
}
