//
// Created by morfeush22 on 06.03.19.
//

#ifndef LOAD_BALANCER_SCHEDULINGSTRATEGY_H
#define LOAD_BALANCER_SCHEDULINGSTRATEGY_H

#include "ConfigParser.h"
#include "SchedulingAlgorithm.h"
#include <boost/beast/http/string_body.hpp>


class SchedulingStrategy {

public:
    SchedulingStrategy(std::string backend_cookie_name, std::unique_ptr<SchedulingAlgorithm> &&scheduling_algorithm);

    const BackendServerDescription &SelectBackendServer(
            boost::beast::http::request<boost::beast::http::string_body> frontend_headers,
            const std::list<BackendServerDescription> &backend_server_description);

private:
    std::string backend_cookie_name_;
    std::unique_ptr<SchedulingAlgorithm> scheduling_algorithm_;

};


#endif //LOAD_BALANCER_SCHEDULINGSTRATEGY_H
