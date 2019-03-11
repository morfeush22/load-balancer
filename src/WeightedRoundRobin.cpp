//
// Created by morfeush22 on 11.03.19.
//

#include "../include/Logger.h"
#include "../include/WeightedRoundRobin.h"

using namespace std;


WeightedRoundRobin::WeightedRoundRobin() :
        generator_(random_device()()) {}

const BackendServerDescription &
WeightedRoundRobin::SelectBackendServer(const std::list<BackendServerDescription> &backend_servers) {
    int acc_weight = std::accumulate(backend_servers.begin(), backend_servers.end(), 0,
                              [](int acc, const BackendServerDescription &server) {
                                  return acc + server.weight;
                              });

    DEBUG("sum of weights: ", acc_weight);

    std::uniform_real_distribution<double> distribution(0, acc_weight);
    auto rnd = distribution(generator_);

    DEBUG("random number is: ", rnd);

    double acc = 0;
    for (const auto &server : backend_servers) {
        acc += server.weight;
        if (rnd < acc) {
            DEBUG("returning server: ", server);
            return server;
        }
    }

    const auto &front = backend_servers.front();

    WARNING("could not choose server using weights, returning front: ", front);

    return front;
}

void WeightedRoundRobin::UpdateBackendServerStatistics(const BackendServerDescription &, size_t) {
}
