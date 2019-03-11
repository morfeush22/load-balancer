//
// Created by morfeush22 on 06.03.19.
//

#include "../include/Logger.h"
#include "../include/RoundRobin.h"
#include "../include/SchedulingStrategyBuilder.h"
#include "../include/WeightedRoundRobin.h"

using namespace std;


SchedulingStrategyBuilder::SchedulingStrategyBuilder(shared_ptr<ConfigParser> config_parser) :
        algorithm_(config_parser->BackendAlgorithm()),
        backend_cookie_name_(config_parser->BackendCookieName()) {}

shared_ptr<SchedulingStrategy> SchedulingStrategyBuilder::ConstructSchedulingStrategy() {
    if (algorithm_ == "round_robin") {
        DEBUG("using round robin algorithm");
        return make_shared<SchedulingStrategy>(backend_cookie_name_, make_unique<RoundRobin>());
    } else if (algorithm_ == "weighted_round_robin") {
        DEBUG("using weighted round robin algorithm");
        return make_shared<SchedulingStrategy>(backend_cookie_name_, make_unique<WeightedRoundRobin>());
    } else {
        WARNING("using default round robin algorithm");
        return make_shared<SchedulingStrategy>(backend_cookie_name_, make_unique<RoundRobin>());
    }
}
