//
// Created by morfeush22 on 04.03.19.
//

#ifndef LOAD_BALANCER_ROUNDROBINSTRATEGY_H
#define LOAD_BALANCER_ROUNDROBINSTRATEGY_H

#include "SchedulingStrategy.h"
#include "../include/ConfigParser.h"


class RoundRobinStrategy: public SchedulingStrategy {

    public:
    //TODO implementation
    boost::optional<BackendServerDescription> SelectBackendServer(const std::list<BackendServerDescription> & backend_server_description);

};


#endif //LOAD_BALANCER_ROUNDROBINSTRATEGY_H
