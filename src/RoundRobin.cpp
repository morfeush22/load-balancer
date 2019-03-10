//
// Created by morfeush22 on 04.03.19.
//

#include "../include/Logger.h"
#include "../include/RoundRobin.h"
#include <algorithm>

using namespace std;


//TODO implementation
const BackendServerDescription &
RoundRobin::SelectBackendServer(const list<BackendServerDescription> &backend_servers) {
    const auto &front = backend_servers.front();

    DEBUG("previously chosen: ", previously_chosen_);

    auto it = find(backend_servers.begin(), backend_servers.end(), previously_chosen_);
    if (it == backend_servers.end()) {
        DEBUG("previously chosen not found, returning front: ", front);
        previously_chosen_ = front;
        return previously_chosen_;
    }

    ++it;
    if (it == backend_servers.end()) {
        DEBUG("end of list, returning front: ", front);
        previously_chosen_ = front;
    } else {
        DEBUG("returning next: ", *it);
        previously_chosen_ = *it;
    }

    return previously_chosen_;
}

void RoundRobin::UpdateBackendServerStatistics(const BackendServerDescription &, size_t) {
}
