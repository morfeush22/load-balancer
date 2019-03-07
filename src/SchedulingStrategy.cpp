//
// Created by morfeush22 on 07.03.19.
//

#include "../include/SchedulingStrategy.h"

SchedulingStrategy::SchedulingStrategy(std::unique_ptr<SchedulingAlgorithm> &&scheduling_algorithm):
scheduling_algorithm_(move(scheduling_algorithm))
{}

const BackendServerDescription &
SchedulingStrategy::SelectBackendServer(boost::beast::http::request<boost::beast::http::string_body> frontend_headers,
                                        const std::list<BackendServerDescription> &backend_server_description) {
    return scheduling_algorithm_->SelectBackendServer(backend_server_description);
}
