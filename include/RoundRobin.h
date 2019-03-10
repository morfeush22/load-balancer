//cookie_name_
// Created by morfeush22 on 04.03.19.
//

#ifndef LOAD_BALANCER_ROUNDROBINSTRATEGY_H
#define LOAD_BALANCER_ROUNDROBINSTRATEGY_H

#include "ConfigParser.h"
#include "SchedulingAlgorithm.h"
#include "SchedulingStrategy.h"


class RoundRobin : public SchedulingAlgorithm {

public:
    const BackendServerDescription &SelectBackendServer(
            const std::list<BackendServerDescription> &backend_servers) override;

    void UpdateBackendServerStatistics(const BackendServerDescription &, std::size_t) override;

private:
    BackendServerDescription previously_chosen_;

};


#endif //LOAD_BALANCER_ROUNDROBINSTRATEGY_H
