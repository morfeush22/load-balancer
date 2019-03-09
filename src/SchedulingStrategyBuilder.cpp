//
// Created by morfeush22 on 06.03.19.
//

#include "../include/SchedulingStrategyBuilder.h"
#include "../include/RoundRobin.h"
#include "../include/Logger.h"


SchedulingStrategyBuilder::SchedulingStrategyBuilder(std::shared_ptr<ConfigParser> config_parser) :
        algorithm_(config_parser->BackendAlgorithm()),
        cookie_name_(config_parser->BackendAlgorithm()) {}

std::shared_ptr<SchedulingStrategy> SchedulingStrategyBuilder::ConstructSchedulingStrategy() {
    if (algorithm_ == "round_robin") {
        DEBUG("using round robin algorithm");
        return std::make_shared<SchedulingStrategy>(std::make_unique<RoundRobin>(cookie_name_));
    } else {
        WARNING("using default round robin algorithm");
        return std::make_shared<SchedulingStrategy>(std::make_unique<RoundRobin>(cookie_name_));
    }
}
