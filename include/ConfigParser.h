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
    bool health_check;

    friend std::ostream &operator<<(std::ostream &stream, const BackendServerDescription &desc) {
        stream << "server_id:\t" << desc.id << "\n"
               << "\t\t" << desc.address << "\n"
               << "\t\t" << desc.port << "\n"
               << "\t\t" << desc.health_check << "\n";

        return stream;
    }

    operator bool() const {
        return id.empty() && address.empty() && port.empty();
    }
};

class ConfigParser {

public:
    explicit ConfigParser(std::string config_file_path);

    void ParseConfigFile();

    bool IsConfigValid();

    std::string LogLevel();

    std::string FrontendAddress();

    std::string FrontendPort();

    std::list<BackendServerDescription> BackendServers();

    unsigned int BackendHealthCheckPeriod();

    std::string BackendHealthCheckEndpoint();

    std::string BackendAlgorithm();

    std::string BackendCookieName();


private:
    std::string config_file_path_;
    boost::property_tree::ptree property_tree_;

};


#endif //LOAD_BALANCER_CONFIGPARSER_H
