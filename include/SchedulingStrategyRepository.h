//
// Created by morfeush22 on 06.03.19.
//

#ifndef LOAD_BALANCER_SCHEDULINGSTRATEGYFACTORY_H
#define LOAD_BALANCER_SCHEDULINGSTRATEGYFACTORY_H

#include "ConfigParser.h"
#include "SchedulingStrategy.h"


class SchedulingStrategyRepository {

    public:
    explicit SchedulingStrategyRepository(std::shared_ptr<ConfigParser> config_parser);
    std::shared_ptr<SchedulingStrategy> GetSchedulingStrategy();

    private:
    std::shared_ptr<SchedulingStrategy> scheduling_strategy_;
    std::string algorithm_;

    void ConstructStrategy();
};


#endif //LOAD_BALANCER_SCHEDULINGSTRATEGYFACTORY_H
