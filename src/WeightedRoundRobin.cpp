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
    int sum = std::accumulate(backend_servers.begin(), backend_servers.end(), 0,
                              [](int acc, const BackendServerDescription &backend_server_description) {
                                  return acc + backend_server_description.weight;
                              });

    DEBUG("sum of weights: ", sum);

    return backend_servers.front();
}

void WeightedRoundRobin::UpdateBackendServerStatistics(const BackendServerDescription &, size_t) {
}
