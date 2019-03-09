//
// Created by morfeush22 on 04.03.19.
//

#include "../include/BackendServersRepository.h"

using namespace std;


BackendServersRepository::BackendServersRepository(
        unique_ptr<HealthCheckerFactory> &&health_checker_factory,
        shared_ptr<ConfigParser> config_parser) :
        health_checker_factory_(move(health_checker_factory)),
        backend_servers_(config_parser->BackendServers()) {
    StartHealthChecking();
}

void BackendServersRepository::StartHealthChecking() {
    for (const auto &server: backend_servers_) {
        if (server.health_check) {
            auto health_checker = health_checker_factory_->MakeHealthChecker();
            health_checker->run(server.address, server.port);
            health_checkers_[server.id] = move(health_checker);
        }
    }
}

list<BackendServerDescription> BackendServersRepository::GetAllServers() {
    list<BackendServerDescription> servers;

    for (const auto &server: backend_servers_) {
        if (!server.health_check || health_checkers_[server.id]->Healthy()) {
            servers.emplace_back(server);
        }
    }

    return servers;
}
