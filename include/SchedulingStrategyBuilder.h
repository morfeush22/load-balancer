//
// Created by morfeush22 on 06.03.19.
//

#ifndef LOAD_BALANCER_SCHEDULINGSTRATEGYFACTORY_H
#define LOAD_BALANCER_SCHEDULINGSTRATEGYFACTORY_H

#include "ConfigParser.h"
#include "SchedulingStrategy.h"


class SchedulingStrategyBuilder {

public:
    explicit SchedulingStrategyBuilder(std::shared_ptr<ConfigParser> config_parser);

    std::shared_ptr<SchedulingStrategy> ConstructSchedulingStrategy();

private:
    std::string algorithm_;
    std::string cookie_name_;

};


#endif //LOAD_BALANCER_SCHEDULINGSTRATEGYFACTORY_H
