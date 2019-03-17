//
// Created by morfeush22 on 07.03.19.
//

#include "../include/Logger.h"
#include "../include/SchedulingStrategy.h"

using namespace std;


SchedulingStrategy::SchedulingStrategy(std::string backend_cookie_name,
                                       std::unique_ptr<SchedulingAlgorithm> &&scheduling_algorithm) :
        backend_cookie_name_(move(backend_cookie_name)),
        scheduling_algorithm_(move(scheduling_algorithm)) {}

// list can not be empty
const BackendServerDescription &
SchedulingStrategy::SelectBackendServer(
        const boost::beast::http::request<boost::beast::http::string_body> &frontend_headers,
        const list<BackendServerDescription> &backend_servers) {
    const BackendServerDescription *backend_server_description = nullptr;

    auto cookie = frontend_headers.base()["Cookie"];
    if (!backend_cookie_name_.empty() && !cookie.empty() && cookie.find(backend_cookie_name_) != string::npos) {
        DEBUG("found feasible cookie: ", cookie);

        auto server_id = cookie.substr(backend_cookie_name_.length() + 1);

        DEBUG("server id from cookie: ", server_id);

        for (auto const &server: backend_servers) {
            if (server.id == server_id) {
                backend_server_description = &server;
            }
        }
    }

    if (backend_server_description) {
        DEBUG("cookie found and server healthy: ", backend_server_description->id);
        return *backend_server_description;
    } else {
        DEBUG("using algorithm to choose server");
        return scheduling_algorithm_->SelectBackendServer(backend_servers);
    }
}
