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
    //TODO implementation
    const BackendServerDescription & SelectBackendServer(const std::list<BackendServerDescription> & backend_server_description) override;

};


#endif //LOAD_BALANCER_ROUNDROBINSTRATEGY_H
