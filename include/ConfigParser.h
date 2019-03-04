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

    friend std::ostream & operator<<(std::ostream &stream, const BackendServerDescription &desc) {
        stream << "server_id:\t" << desc.id << "\n"
            << "\t\t" << desc.address << "\n"
            << "\t\t" << desc.port << "\n"
            << "\t\t" << desc.health_check << "\n";

        return stream;
    }
};

class ConfigParser {

    public:
    explicit ConfigParser(std::string config_file_path);
    void ParseConfigFile();
    std::string FrontendAdress();
    std::string FrontendPort();
    std::list<BackendServerDescription> BackendServers();
    unsigned int BackendHealthCheckPeriod();
    std::string BackendHealthCheckEndpoint();
    std::string BackendAlorithm();
    std::string BackendCookieName();


    private:
    std::string _config_file_path;
    boost::property_tree::ptree _property_tree;

};


#endif //LOAD_BALANCER_CONFIGPARSER_H
