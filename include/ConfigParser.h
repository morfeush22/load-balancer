//
// Created by morfeush22 on 25.02.19.
//

#ifndef LOAD_BALANCER_CONFIGPARSER_H
#define LOAD_BALANCER_CONFIGPARSER_H

#include <boost/property_tree/ptree.hpp>
#include <string>


class ConfigParser {

    public:
    ConfigParser(std::string config_file_path);
    void ParseConfigFile();

    private:
    std::string _config_file_path;
    boost::property_tree::ptree _property_tree;

};


#endif //LOAD_BALANCER_CONFIGPARSER_H
