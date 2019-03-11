//
// Created by morfeush22 on 05.03.19.
//

#include "../include/ProxyConnectionFactory.h"
#include <curses.h>

using namespace std;


ProxyConnectionFactory::ProxyConnectionFactory(boost::asio::io_context &io_context,
                                               std::shared_ptr<BackendServersRepository> backend_servers_repository,
                                               std::shared_ptr<SchedulingStrategy> scheduling_strategy,
                                               std::shared_ptr<ConfigParser> config_parser) :
        backend_insert_cookie_(config_parser->BackendInsertCookie()),
        backend_cookie_name_(move(config_parser->BackendCookieName())),
        io_context_(io_context),
        servers_repository_(move(backend_servers_repository)),
        scheduling_strategy_(move(scheduling_strategy)) {}

shared_ptr<ProxyConnection> ProxyConnectionFactory::MakeProxyConnection() {
    return make_shared<ProxyConnection>(io_context_, servers_repository_, scheduling_strategy_, backend_insert_cookie_,
                                        backend_cookie_name_);
}
