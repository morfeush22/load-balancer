//
// Created by morfeush22 on 07.03.19.
//

#ifndef LOAD_BALANCER_SCHEDULINGALGORITHM_H
#define LOAD_BALANCER_SCHEDULINGALGORITHM_H


class SchedulingAlgorithm {

public:
    /**
     * Functions selects backend server that will be used to handle next client request.
     * @param backend_servers Non-empty list of healthy backend servers
     * @return Reference to chosen backend server
     */
    virtual const BackendServerDescription &SelectBackendServer(
            const std::list <BackendServerDescription> &backend_servers) = 0;

    /**
     * Not implemented
     * @param backend_server_description
     * @param bytes_transferred
     */
    virtual void UpdateBackendServerStatistics(const BackendServerDescription &backend_server_description,
            std::size_t bytes_transferred) = 0;

    /**
     * Class is abstract, so we need virtual destructor
     */
    virtual ~SchedulingAlgorithm() = default;

};

#endif //LOAD_BALANCER_SCHEDULINGALGORITHM_H
