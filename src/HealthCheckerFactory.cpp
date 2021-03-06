//
// Created by morfeush22 on 04.03.19.
//

#include "../include/HealthCheckerFactory.h"

namespace asio = boost::asio;
using namespace std;


HealthCheckerFactory::HealthCheckerFactory(asio::io_context &io_context, shared_ptr<ConfigParser> config_parser) :
        health_check_endpoint_(config_parser->BackendHealthCheckEndpoint()),
        health_check_period_(config_parser->BackendHealthCheckPeriod()),
        io_context_(io_context) {}

shared_ptr<HealthChecker> HealthCheckerFactory::MakeHealthChecker() {
    return make_shared<HealthChecker>(io_context_, health_check_endpoint_, health_check_period_);
}
