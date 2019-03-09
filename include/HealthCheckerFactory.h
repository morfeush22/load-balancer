//
// Created by morfeush22 on 04.03.19.
//

#ifndef LOAD_BALANCER_HEALTHCHECKERFACTORY_H
#define LOAD_BALANCER_HEALTHCHECKERFACTORY_H

#include "ConfigParser.h"
#include "HealthChecker.h"
#include <boost/asio.hpp>


class HealthCheckerFactory {

    public:
    explicit HealthCheckerFactory(boost::asio::io_context &io_context, std::shared_ptr<ConfigParser> config_parser);
    std::shared_ptr<HealthChecker> MakeHealthChecker();

    private:
    std::string health_check_endpoint_;
    unsigned int health_check_period_;
    boost::asio::io_context &io_context_;

};


#endif //LOAD_BALANCER_HEALTHCHECKERFACTORY_H
