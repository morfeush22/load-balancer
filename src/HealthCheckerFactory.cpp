//
// Created by morfeush22 on 04.03.19.
//

#include "../include/HealthCheckerFactory.h"

namespace asio = boost::asio;


HealthCheckerFactory::HealthCheckerFactory(asio::io_context &io_context, std::shared_ptr<ConfigParser> config_parser):
io_context_(io_context),
config_parser_(move(config_parser))
{}

std::shared_ptr<HealthChecker> HealthCheckerFactory::MakeHealthChecker() {
    return std::make_shared<HealthChecker>(io_context_, config_parser_->BackendHealthCheckPeriod(), config_parser_->BackendHealthCheckEndpoint());
}
