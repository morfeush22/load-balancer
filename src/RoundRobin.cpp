//
// Created by morfeush22 on 04.03.19.
//

#include "../include/RoundRobin.h"

using namespace std;


//TODO implementation
const BackendServerDescription &
RoundRobin::SelectBackendServer(const list<BackendServerDescription> &backend_server_description) {
    return backend_server_description.front();
}

void RoundRobin::UpdateBackendServerStatistics(
        const BackendServerDescription &SelectBackendServer,
        size_t bytes_transferred) {
    boost::ignore_unused(bytes_transferred);
}
