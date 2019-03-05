//
// Created by morfeush22 on 04.03.19.
//

#include "../include/RoundRobinStrategy.h"

const BackendServerDescription &
RoundRobinStrategy::ChooseBackendServer(const std::list<BackendServerDescription> & backend_server_description) {
    return backend_server_description.front();
}
