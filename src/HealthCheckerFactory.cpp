//
// Created by morfeush22 on 04.03.19.
//

#include "../include/HealthCheckerFactory.h"

namespace asio = boost::asio;


HealthCheckerFactory::HealthCheckerFactory(asio::io_context &io_context, std::shared_ptr<ConfigParser> config_parser):
_io_context(io_context),
_config_parser(move(config_parser))
{}

std::shared_ptr<HealthChecker> HealthCheckerFactory::MakeHealthChecker() {
    return std::make_shared<HealthChecker>(_io_context, _config_parser->BackendHealthCheckPeriod(), _config_parser->BackendHealthCheckEndpoint());
}
