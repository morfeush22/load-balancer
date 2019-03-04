//
// Created by morfeush22 on 04.03.19.
//

#ifndef LOAD_BALANCER_HEALTHCHECKERFACTORY_H
#define LOAD_BALANCER_HEALTHCHECKERFACTORY_H

#include "../include/ConfigParser.h"
#include "../include/HealthChecker.h"
#include <boost/asio.hpp>


class HealthCheckerFactory {

    public:
    explicit HealthCheckerFactory(boost::asio::io_context &io_context, std::shared_ptr<ConfigParser> config_parser);
    std::shared_ptr<HealthChecker> MakeHealthChecker();

    private:
    boost::asio::io_context &_io_context;
    std::shared_ptr<ConfigParser> _config_parser;

};


#endif //LOAD_BALANCER_HEALTHCHECKERFACTORY_H
