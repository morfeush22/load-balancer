//
// Created by morfeush22 on 11.03.19.
//

#ifndef LOAD_BALANCER_WEIGHTEDROUNDROBIN_H
#define LOAD_BALANCER_WEIGHTEDROUNDROBIN_H

#include "ConfigParser.h"
#include "SchedulingAlgorithm.h"
#include <list>
#include <random>


class WeightedRoundRobin : public SchedulingAlgorithm {

public:
    WeightedRoundRobin();

    const BackendServerDescription &SelectBackendServer(
            const std::list<BackendServerDescription> &backend_servers) override;

    void UpdateBackendServerStatistics(const BackendServerDescription &, std::size_t) override;

private:
    std::mt19937 generator_;

};


#endif //LOAD_BALANCER_WEIGHTEDROUNDROBIN_H
