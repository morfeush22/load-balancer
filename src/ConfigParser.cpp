//
// Created by morfeush22 on 25.02.19.
//

#include "../include/ConfigParser.h"
#include <boost/algorithm/string.hpp>
#include <boost/property_tree/ini_parser.hpp>

namespace prop_tree = boost::property_tree;
using namespace std;


ConfigParser::ConfigParser(string config_file_path) {
    config_file_path_ = move(config_file_path);
}

void ConfigParser::ParseConfigFile() {
    prop_tree::ini_parser::read_ini(config_file_path_, property_tree_);
}

string ConfigParser::FrontendAddress() {
    return property_tree_.get<string>("frontend.address");
}

string ConfigParser::FrontendPort() {
    return property_tree_.get<string>("frontend.port");
}

list<BackendServerDescription> ConfigParser::BackendServers() {
    list<BackendServerDescription> servers;

    auto servers_config = property_tree_.get<string>("backend.servers");
    vector<string> servers_references;
    boost::split(servers_references, servers_config, boost::is_any_of(","));

    for (auto &id: servers_references) {
        BackendServerDescription desc;

        desc.id = id;

        auto child = property_tree_.get_child(id);
        desc.address = child.get<string>("address");
        desc.port = child.get<string>("port");
        desc.health_check = child.get<bool>("health_check");

        servers.push_back(move(desc));
    }

    return servers;
}

unsigned int ConfigParser::BackendHealthCheckPeriod() {
    return property_tree_.get<unsigned int>("backend.health_check_period");
}

string ConfigParser::BackendHealthCheckEndpoint() {
    return property_tree_.get<string>("backend.health_check_endpoint");
}

string ConfigParser::BackendAlgorithm() {
    return property_tree_.get<string>("backend.algorithm");
}

string ConfigParser::BackendCookieName() {
    return property_tree_.get<string>("backend.cookie_name");
}

string ConfigParser::LogLevel() {
    return property_tree_.get<string>("all.log_level");
}

bool ConfigParser::IsConfigValid() {
    //TODO implementation
    return true;
}

bool ConfigParser::BackendInsertCookie() {
    return property_tree_.get<bool>("backend.insert_cookie");
}


