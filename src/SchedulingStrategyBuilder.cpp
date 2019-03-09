//
// Created by morfeush22 on 06.03.19.
//

#include "../include/Logger.h"
#include "../include/RoundRobin.h"
#include "../include/SchedulingStrategyBuilder.h"

using namespace std;


SchedulingStrategyBuilder::SchedulingStrategyBuilder(shared_ptr<ConfigParser> config_parser) :
        algorithm_(config_parser->BackendAlgorithm()),
        cookie_name_(config_parser->BackendAlgorithm()) {}

shared_ptr<SchedulingStrategy> SchedulingStrategyBuilder::ConstructSchedulingStrategy() {
    if (algorithm_ == "round_robin") {
        DEBUG("using round robin algorithm");
        return make_shared<SchedulingStrategy>(make_unique<RoundRobin>(cookie_name_));
    } else {
        WARNING("using default round robin algorithm");
        return make_shared<SchedulingStrategy>(make_unique<RoundRobin>(cookie_name_));
    }
}
