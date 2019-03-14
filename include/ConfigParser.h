//
// Created by morfeush22 on 25.02.19.
//

#ifndef LOAD_BALANCER_CONFIGPARSER_H
#define LOAD_BALANCER_CONFIGPARSER_H

#include <boost/property_tree/ptree.hpp>
#include <list>
#include <string>


/**
 * Structure that holds variables describing configured backend servers.
 */
struct BackendServerDescription {

    /// ID of backend server as in configuration file
    std::string id;
    /// IP address of backend server
    std::string address;
    /// Port number of backend server
    std::string port;
    /// Weight of backend server, used by Weighted Round Robin algorithm
    unsigned int weight;
    /// Flag indicating if that backend server should be health-checked
    bool health_check;

    /**
     * Provides pretty-print of BackendServerDescription structure.
     * @param stream Reference to std::ostream object
     * @param desc Reference to BackendServerDescription object
     * @return Reference to std::ostream object
     */
    friend std::ostream &operator<<(std::ostream &stream, const BackendServerDescription &desc) {
        stream << "server_id: " << desc.id
               << ", server_address: " << desc.address
               << ", server_port: " << desc.port
               << ", weight: " << desc.weight
               << ", server_is_being_checked: " << desc.health_check;

        return stream;
    }

    /**
     * Provides equality operator for comparing BackendServerDescription objects.
     * @param first Reference to first BackendServerDescription object
     * @param second Reference to second BackendServerDescription object
     * @return True if objects are equal, false otherwise
     */
    friend bool operator==(const BackendServerDescription &first, const BackendServerDescription &second) {
        return first.id == second.id &&
               first.address == second.address &&
               first.port == second.port &&
               first.weight == second.weight &&
               first.health_check == second.health_check;
    }

};

class ConfigParser {

public:
    /**
     * Parses and validates configuration file.
     * @param config_file_path Path to configuration file
     */
    explicit ConfigParser(std::string config_file_path);

    /**
     * Parses configuration file. Must be called before accessing any fields.
     */
    void ParseConfigFile();

    /**
     * Indicates whether passed configuration file is valid.
     * @return True if configuration file is valid, false otherwise
     */
    bool ConfigValid();

    /**
     *
     * @return Configured logging level
     */
    std::string LogLevel();

    /**
     *
     * @return Configured address of frontend server
     */
    std::string FrontendAddress();

    /**
     *
     * @return Configured port of frontend server
     */
    std::string FrontendPort();

    /**
     *
     * @return List of configured backend servers
     */
    std::list<BackendServerDescription> BackendServers();

    /**
     *
     * @return Configured health checking period
     */
    unsigned int BackendHealthCheckPeriod();

    /**
     *
     * @return Configured health checking path
     */
    std::string BackendHealthCheckEndpoint();

    /**
     *
     * @return Name of algorithm used to elect backend server
     */
    std::string BackendAlgorithm();

    /**
     *
     * @return Name of cookie that will be checked to first-priority election of backend server, can be empty
     */
    std::string BackendCookieName();

    /**
     *
     * @return Whether to insert cookie named BackendCookieName() in backend server responses to enable stickiness
     */
    bool BackendInsertCookie();


private:
    std::string config_file_path_;
    bool config_valid_ = false;
    boost::property_tree::ptree property_tree_;

};


#endif //LOAD_BALANCER_CONFIGPARSER_H
