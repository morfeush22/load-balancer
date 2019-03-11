//
// Created by morfeush22 on 25.02.19.
//

#ifndef LOAD_BALANCER_CONFIGPARSER_H
#define LOAD_BALANCER_CONFIGPARSER_H

#include <boost/property_tree/ptree.hpp>
#include <list>
#include <string>


struct BackendServerDescription {

    std::string id;
    std::string address;
    std::string port;
    unsigned int weight;
    bool health_check;

    friend std::ostream &operator<<(std::ostream &stream, const BackendServerDescription &desc) {
        stream << "server_id: " << desc.id
               << ", server_address: " << desc.address
               << ", server_port: " << desc.port
               << ", weight: " << desc.weight
               << ", server_is_being_checked: " << desc.health_check;

        return stream;
    }

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
    explicit ConfigParser(std::string config_file_path);

    void ParseConfigFile();

    bool ConfigValid();

    std::string LogLevel();

    std::string FrontendAddress();

    std::string FrontendPort();

    std::list<BackendServerDescription> BackendServers();

    unsigned int BackendHealthCheckPeriod();

    std::string BackendHealthCheckEndpoint();

    std::string BackendAlgorithm();

    std::string BackendCookieName();

    bool BackendInsertCookie();


private:
    std::string config_file_path_;
    bool config_valid_ = false;
    boost::property_tree::ptree property_tree_;

};


#endif //LOAD_BALANCER_CONFIGPARSER_H
