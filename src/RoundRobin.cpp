//
// Created by morfeush22 on 04.03.19.
//

#include "../include/RoundRobin.h"

//TODO implementation
const BackendServerDescription &
RoundRobin::SelectBackendServer(const std::list<BackendServerDescription> &backend_server_description) {
    return backend_server_description.front();
}

void RoundRobin::UpdateBackendServerStatistics(
        const BackendServerDescription &SelectBackendServer,
        std::size_t bytes_transferred) {
    boost::ignore_unused(bytes_transferred);
}
