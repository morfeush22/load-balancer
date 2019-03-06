//
// Created by morfeush22 on 06.03.19.
//

#include "../include/SchedulingStrategyRepository.h"
#include "../include/RoundRobinStrategy.h"

SchedulingStrategyRepository::SchedulingStrategyRepository(std::shared_ptr<ConfigParser> config_parser) {
    algorithm_ = config_parser->BackendAlorithm();
    ConstructStrategy();
}

std::shared_ptr<SchedulingStrategy> SchedulingStrategyRepository::GetSchedulingStrategy() {
    return scheduling_strategy_;
}

void SchedulingStrategyRepository::ConstructStrategy() {
    if (algorithm_ == "round_robin") {
        scheduling_strategy_ = std::make_shared<RoundRobinStrategy>();
    }
}
