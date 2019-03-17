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
    /**
     * Algorithm that can be used to choose backend server. Chooses the next backend server using configured servers weights.
     * Algorithm is pretty dumb, meaning the next server is calculated using uniform distribution, but in longer period
     * that converges to expected values.
     */
    WeightedRoundRobin();

    /**
     * Returns the chosen backend server.
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
    std::mt19937 generator_;

};


#endif //LOAD_BALANCER_WEIGHTEDROUNDROBIN_H
