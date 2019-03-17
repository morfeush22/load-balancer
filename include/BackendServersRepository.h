//
// Created by morfeush22 on 04.03.19.
//

#ifndef LOAD_BALANCER_SERVERSREPOSITORY_H
#define LOAD_BALANCER_SERVERSREPOSITORY_H

#include "ConfigParser.h"
#include "HealthCheckerFactory.h"
#include <boost/optional.hpp>
#include <string>


class BackendServersRepository {

public:
    /**
     * Takes care of maintaining list of healthy backend servers. Uses HealthChecker instances to periodically query
     * servers status.
     * @param health_checker_factory Pointer to HealthCheckerFactory class instance
     * @param config_parser Pointer to ConfigParser class instance
     */
    BackendServersRepository(std::unique_ptr<HealthCheckerFactory> &&health_checker_factory,
                             std::shared_ptr<ConfigParser> config_parser);

    /**
     * Returns the list of healthy backend servers. List can be empty.
     * @return List of healthy backend servers
     */
    std::list<BackendServerDescription> GetAllServers();

private:
    std::list<BackendServerDescription> backend_servers_;
    std::unique_ptr<HealthCheckerFactory> health_checker_factory_;
    std::map<std::string, std::shared_ptr<HealthChecker>> health_checkers_;

    void StartHealthChecking();

};


#endif //LOAD_BALANCER_SERVERSREPOSITORY_H
