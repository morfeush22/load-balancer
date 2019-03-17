//
// Created by morfeush22 on 04.03.19.
//

#ifndef LOAD_BALANCER_ROUNDROBINSTRATEGY_H
#define LOAD_BALANCER_ROUNDROBINSTRATEGY_H

#include "ConfigParser.h"
#include "SchedulingAlgorithm.h"
#include "SchedulingStrategy.h"


class RoundRobin : public SchedulingAlgorithm {

public:
    /**
     * Algorithm that can be used to choose backend server. Keeps the object of previously chosen server, and selects next
     * one as in BackendServerDescription list or front, if next server can not be chosen.
     * @param backend_servers Non-empty list of healthy backend servers
     * @return Reference to chosen backend server
     */
    const BackendServerDescription &SelectBackendServer(
            const std::list<BackendServerDescription> &backend_servers) override;

    /**
     * Not implemented
     */
    void UpdateBackendServerStatistics(const BackendServerDescription &, std::size_t) override;

private:
    BackendServerDescription previously_chosen_;

};


#endif //LOAD_BALANCER_ROUNDROBINSTRATEGY_H
