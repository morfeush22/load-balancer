//
// Created by morfeush22 on 04.03.19.
//

#ifndef LOAD_BALANCER_ROUNDROBINSTRATEGY_H
#define LOAD_BALANCER_ROUNDROBINSTRATEGY_H

#include "SchedulingStrategy.h"
#include "SchedulingAlgorithm.h"
#include "../include/ConfigParser.h"


class RoundRobin: public SchedulingAlgorithm {

public:
    const BackendServerDescription & SelectBackendServer(
            const std::list<BackendServerDescription> & backend_server_description) override;
    void UpdateBackendServerStatistics(
            const BackendServerDescription &SelectBackendServer,
            std::size_t bytes_transferred) override;

};


#endif //LOAD_BALANCER_ROUNDROBINSTRATEGY_H
