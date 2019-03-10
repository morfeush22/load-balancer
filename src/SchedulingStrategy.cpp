//
// Created by morfeush22 on 07.03.19.
//

#include "../include/SchedulingStrategy.h"

using namespace std;


SchedulingStrategy::SchedulingStrategy(std::string backend_cookie_name,
                                       std::unique_ptr<SchedulingAlgorithm> &&scheduling_algorithm) :
        backend_cookie_name_(move(backend_cookie_name)),
        scheduling_algorithm_(move(scheduling_algorithm)) {}

// list can not be empty
const BackendServerDescription &
SchedulingStrategy::SelectBackendServer(boost::beast::http::request<boost::beast::http::string_body> frontend_headers,
                                        const list<BackendServerDescription> &backend_server_description) {


    //TODO implementation
    //if has cookie
    //check list for server by id
    //if server found, use it
    //else choose one from list

    //BackendServerDescription server;
    //foreach...
    //if(!server)
    //get one from scheduling algorithm
    return scheduling_algorithm_->SelectBackendServer(backend_server_description);
}
