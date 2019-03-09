//
// Created by morfeush22 on 05.03.19.
//

#include "../include/ProxyConnectionFactory.h"

//TODO pass scheduling strategy
ProxyConnectionFactory::ProxyConnectionFactory(boost::asio::io_context &io_context,
        std::shared_ptr<ConfigParser> config_parser,
        std::shared_ptr<BackendServersRepository> servers_repository,
        std::shared_ptr<SchedulingStrategy> scheduling_strategy):
io_context_(io_context),
config_parser_(move(config_parser)),
servers_repository_(move(servers_repository)),
scheduling_strategy_(move(scheduling_strategy))
{}

std::shared_ptr<ProxyConnection> ProxyConnectionFactory::MakeProxyConnection() {
    return std::make_shared<ProxyConnection>(io_context_, servers_repository_, scheduling_strategy_);
}
