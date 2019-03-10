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
SchedulingStrategy::SelectBackendServer(boost::beast::http::request<boost::beast::http::string_body> frontend_headers,
                                        const list<BackendServerDescription> &backend_servers) {
    const BackendServerDescription *backend_server_description = nullptr;

    auto cookie = frontend_headers.base()["Cookie"];
    if (!cookie.empty()) {
        DEBUG("found cookie: ", cookie);

        for (auto const &server: backend_servers) {
            if (server.id == cookie) {
                backend_server_description = &server;
            }
        }
    }

    if (backend_server_description) {
        DEBUG("cookie found and server healthy: ", backend_server_description->id);
        return *backend_server_description;
    } else {
        DEBUG("cookie not found or server not healthy");
        return scheduling_algorithm_->SelectBackendServer(backend_servers);
    }
}
