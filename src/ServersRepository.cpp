//
// Created by morfeush22 on 04.03.19.
//

#include "../include/ServersRepository.h"

using namespace std;


ServersRepository::ServersRepository(std::unique_ptr<HealthCheckerFactory> health_checker_factory,
                                     std::shared_ptr<ConfigParser> config_parser):
                                     health_checker_factory_(move(health_checker_factory)),
                                     config_parser_(move(config_parser))
{
    backend_servers_ = config_parser_->BackendServers();
    StartHealthChecking();
}

void ServersRepository::StartHealthChecking() {
    for (auto &server: backend_servers_) {
        if (server.health_check) {
            auto health_checker = health_checker_factory_->MakeHealthChecker();
            health_checker->run(server.address, server.port);
            health_checkers_[server.id] = health_checker;
        }
    }
}

boost::optional<tuple<string, string>> ServersRepository::GetServer(string id) {
    for (auto &server: backend_servers_) {
        if (server.id == id) {
            if (! server.health_check || health_checkers_[id]->healthy()) {
                return std::make_tuple(server.address, server.port);
            }
        }
    }

    return boost::none;
}

list<tuple<string, string>> ServersRepository::GetAllServers() {
    list<tuple<string, string>> servers;

    for (auto &server: backend_servers_) {
        if (! server.health_check || health_checkers_[server.id]->healthy()) {
            servers.emplace_back(server.address, server.port);
        }
    }

    return servers;
}
