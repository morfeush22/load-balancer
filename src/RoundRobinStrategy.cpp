//
// Created by morfeush22 on 04.03.19.
//

#include "../include/RoundRobinStrategy.h"

boost::optional<BackendServerDescription>
RoundRobinStrategy::SelectBackendServer(const std::list<BackendServerDescription> &backend_server_description) {
    return boost::optional<BackendServerDescription>();
}
