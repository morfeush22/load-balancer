//
// Created by morfeush22 on 06.03.19.
//

#ifndef LOAD_BALANCER_SCHEDULINGSTRATEGYFACTORY_H
#define LOAD_BALANCER_SCHEDULINGSTRATEGYFACTORY_H

#include "ConfigParser.h"
#include "SchedulingStrategy.h"


class SchedulingStrategyBuilder {

public:
    /**
     * Takes care of building valid SchedulingStrategy objects.
     * @param config_parser Pointer to ConfigParser class instance
     */
    explicit SchedulingStrategyBuilder(std::shared_ptr<ConfigParser> config_parser);

    /**
     * Constructs new SchedulingStrategy object.
     * @return Newly constructed SchedulingStrategy object
     */
    std::shared_ptr<SchedulingStrategy> ConstructSchedulingStrategy();

private:
    std::string algorithm_;
    std::string backend_cookie_name_;

};


#endif //LOAD_BALANCER_SCHEDULINGSTRATEGYFACTORY_H
