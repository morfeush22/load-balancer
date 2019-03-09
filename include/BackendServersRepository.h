//
// Created by morfeush22 on 04.03.19.
//

#ifndef LOAD_BALANCER_SERVERSREPOSITORY_H
#define LOAD_BALANCER_SERVERSREPOSITORY_H

#include "../include/ConfigParser.h"
#include "../include/HealthCheckerFactory.h"
#include <boost/optional.hpp>
#include <string>


class BackendServersRepository {

public:
    BackendServersRepository(std::unique_ptr<HealthCheckerFactory> &&health_checker_factory,
                             std::shared_ptr<ConfigParser> config_parser);

    std::list<BackendServerDescription> GetAllServers();

private:
    std::list<BackendServerDescription> backend_servers_;
    std::unique_ptr<HealthCheckerFactory> health_checker_factory_;
    std::map<std::string, std::shared_ptr<HealthChecker>> health_checkers_;

    void StartHealthChecking();

};


#endif //LOAD_BALANCER_SERVERSREPOSITORY_H
