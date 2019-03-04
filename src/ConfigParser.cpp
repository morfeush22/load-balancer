//
// Created by morfeush22 on 25.02.19.
//

#include "../include/ConfigParser.h"
#include <boost/algorithm/string.hpp>
#include <boost/property_tree/ini_parser.hpp>

namespace prop_tree = boost::property_tree;
using namespace std;


ConfigParser::ConfigParser(string config_file_path) {
    _config_file_path = move(config_file_path);
}

void ConfigParser::ParseConfigFile() {
    prop_tree::ini_parser::read_ini(_config_file_path, _property_tree);
}

std::string ConfigParser::FrontendAdress() {
    return _property_tree.get<string>("frontend.address");
}

std::string ConfigParser::FrontendPort() {
    return _property_tree.get<string>("frontend.port");
}

list<BackendServerDescription> ConfigParser::BackendServers() {
   list<BackendServerDescription> servers;

   auto s = _property_tree.get<std::string>("backend.servers");
   vector<string> ss;
   boost::split(ss, s, boost::is_any_of(","));

   for (auto &id: ss) {
       BackendServerDescription desc;

       desc.id = id;

       auto child = _property_tree.get_child(id);
       desc.address = child.get<string>("address");
       desc.port = child.get<string>("port");
       desc.health_check = child.get<bool>("health_check");

       servers.push_back(move(desc));
   }

    return servers;
}

unsigned int ConfigParser::BackendHealthCheckPeriod() {
    return _property_tree.get<unsigned int>("backend.health_check_period");
}

std::string ConfigParser::BackendHealthCheckEndpoint() {
    return _property_tree.get<string>("backend.health_check_endpoint");
}

std::string ConfigParser::BackendAlorithm() {
    return _property_tree.get<string>("backend.algorithm");
}

std::string ConfigParser::BackendCookieName() {
    return _property_tree.get<string>("backend.cookie_name");
}


