//
// Created by morfeush22 on 07.03.19.
//

#include "../include/SchedulingStrategy.h"

SchedulingStrategy::SchedulingStrategy(std::unique_ptr<SchedulingAlgorithm> &&scheduling_algorithm):
scheduling_algorithm_(move(scheduling_algorithm))
{}

// list can not be empty
const BackendServerDescription &
SchedulingStrategy::SelectBackendServer(boost::beast::http::request<boost::beast::http::string_body> frontend_headers,
                                        const std::list<BackendServerDescription> &backend_server_description) {
    //if has cookie
    //get server by id
    //if server not empty, use it
    //else choose one from list
    return scheduling_algorithm_->SelectBackendServer(backend_server_description);
}
