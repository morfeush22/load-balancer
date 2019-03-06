//
// Created by morfeush22 on 06.03.19.
//

#ifndef LOAD_BALANCER_SCHEDULINGSTRATEGY_H
#define LOAD_BALANCER_SCHEDULINGSTRATEGY_H


#include "ConfigParser.h"

class SchedulingStrategy {

    public:
    virtual const BackendServerDescription & SelectBackendServer(const std::list<BackendServerDescription> & backend_server_description) = 0;
};


#endif //LOAD_BALANCER_SCHEDULINGSTRATEGY_H
