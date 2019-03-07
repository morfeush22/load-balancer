//
// Created by morfeush22 on 07.03.19.
//

#ifndef LOAD_BALANCER_SCHEDULINGALGORITHM_H
#define LOAD_BALANCER_SCHEDULINGALGORITHM_H


class SchedulingAlgorithm {

public:
    virtual const BackendServerDescription &SelectBackendServer(
            const std::list <BackendServerDescription> &backend_server_description) = 0;


};

#endif //LOAD_BALANCER_SCHEDULINGALGORITHM_H
