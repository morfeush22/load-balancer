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
    /**
     * Takes care of prioritizing client cookie setting or using SchedulingAlgorithm otherwise. If client cookie is set,
     * and indicated backend server is healthy, SchedulingStrategy will always return cookie indicated backend server. Otherwise,
     * SchedulingAlgorithm will be used.
     * @param backend_cookie_name Name of cookie to be looked for in client headers, can be empty to disable search
     * @param scheduling_algorithm Pointer to SchedulingAlgorithm class instance
     */
    SchedulingStrategy(std::string backend_cookie_name, std::unique_ptr<SchedulingAlgorithm> &&scheduling_algorithm);

    /**
     * Returns the chosen backend server.
     * @param frontend_headers Reference to object that holds client headers
     * @param backend_servers Non-empty list of healthy backend servers
     * @return Reference to chosen backend server
     */
    const BackendServerDescription &SelectBackendServer(
            const boost::beast::http::request<boost::beast::http::string_body> &frontend_headers,
            const std::list<BackendServerDescription> &backend_servers);

private:
    std::string backend_cookie_name_;
    std::unique_ptr<SchedulingAlgorithm> scheduling_algorithm_;

};


#endif //LOAD_BALANCER_SCHEDULINGSTRATEGY_H
