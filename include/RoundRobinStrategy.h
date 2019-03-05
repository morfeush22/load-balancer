//
// Created by morfeush22 on 04.03.19.
//

#ifndef LOAD_BALANCER_ROUNDROBINSTRATEGY_H
#define LOAD_BALANCER_ROUNDROBINSTRATEGY_H

#include "../include/ConfigParser.h"


class RoundRobinStrategy {

    public:
    //TODO implementation
    const BackendServerDescription & ChooseBackendServer(const std::list<BackendServerDescription> & backend_server_description);

};


#endif //LOAD_BALANCER_ROUNDROBINSTRATEGY_H
