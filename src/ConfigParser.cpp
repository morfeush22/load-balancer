//
// Created by morfeush22 on 25.02.19.
//

#include "../include/ConfigParser.h"
#include "../include/Logger.h"
#include <boost/algorithm/string.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <iostream>

#define DEFAULT_WEIGHT 1
#define DEFAULT_BACKEND_HEALTH_CHECK_PERIOD 60
#define DEFAULT_BACKEND_HEALTH_CHECK_ENDPOINT ""
#define DEFAULT_BACKEND_ALGORITHM "round_robin"
#define DEFAULT_BACKEND_COOKIE_NAME ""
#define DEFAULT_LOG_LEVEL "error"
#define DEFAULT_LOG_FILE_PATH ""
#define DEFAULT_BACKEND_INSERT_COOKIE false

namespace prop_tree = boost::property_tree;
using namespace std;


ConfigParser::ConfigParser(string config_file_path) {
    config_file_path_ = move(config_file_path);
}

void ConfigParser::ParseConfigFile() {
    try {
        prop_tree::ini_parser::read_ini(config_file_path_, property_tree_);
        config_valid_ = true;
    } catch (prop_tree::ini_parser::ini_parser_error &e) {
        cerr << "No such file: " << config_file_path_ << "\n";
        config_valid_ = false;
    }
}

string ConfigParser::FrontendAddress() {
    auto frontend_address = property_tree_.get_optional<string>("frontend.address");

    if (!frontend_address) {
        ERROR("wrong or missing frontend.address");
        exit(EXIT_FAILURE);
    }

    return frontend_address.value();
}

string ConfigParser::FrontendPort() {
    auto frontend_port = property_tree_.get_optional<string>("frontend.port");

    if (!frontend_port) {
        ERROR("wrong or missing frontend.port");
        exit(EXIT_FAILURE);
    }

    return frontend_port.value();
}

list<BackendServerDescription> ConfigParser::BackendServers() {
    list<BackendServerDescription> servers;

    auto servers_config = property_tree_.get_optional<string>("backend.servers");

    if (!servers_config) {
        ERROR("wrong or missing backend.servers");
        exit(EXIT_FAILURE);
    }

    vector<string> servers_references;
    boost::split(servers_references, servers_config.value(), boost::is_any_of(","));

    try {
        for (auto &id: servers_references) {
            BackendServerDescription desc;

            desc.id = id;

            auto child = property_tree_.get_child(id);
            desc.address = child.get<string>("address");
            desc.port = child.get<string>("port");
            desc.weight = child.get<unsigned int>("weight", DEFAULT_WEIGHT);
            desc.health_check = child.get<bool>("health_check");

            servers.push_back(move(desc));
        }
    } catch (prop_tree::ptree_error &e) {
        ERROR("wrong structure of server description");
        exit(EXIT_FAILURE);
    }

    return servers;
}

unsigned int ConfigParser::BackendHealthCheckPeriod() {
    auto backend_health_check_period = property_tree_.get_optional<unsigned int>("backend.health_check_period");

    if (!backend_health_check_period) {
        WARNING("wrong or missing backend.health_check_period, using: '", DEFAULT_BACKEND_HEALTH_CHECK_PERIOD, "'");
        return DEFAULT_BACKEND_HEALTH_CHECK_PERIOD;
    }

    return backend_health_check_period.value();
}

string ConfigParser::BackendHealthCheckEndpoint() {
    auto backend_health_check_endpoint = property_tree_.get_optional<string>("backend.health_check_endpoint");

    if (!backend_health_check_endpoint) {
        WARNING("wrong or missing backend.health_check_endpoint, using: '", DEFAULT_BACKEND_HEALTH_CHECK_ENDPOINT, "'");
        return DEFAULT_BACKEND_HEALTH_CHECK_ENDPOINT;
    }

    return backend_health_check_endpoint.value();
}

string ConfigParser::BackendAlgorithm() {
    auto backend_algorithm = property_tree_.get_optional<string>("backend.algorithm");

    if (!backend_algorithm) {
        WARNING("wrong or missing backend.algorithm, using: '", DEFAULT_BACKEND_ALGORITHM, "'");
        return DEFAULT_BACKEND_ALGORITHM;
    }

    return backend_algorithm.value();
}

string ConfigParser::BackendCookieName() {
    auto backend_cookie_name = property_tree_.get_optional<string>("backend.cookie_name");

    if (!backend_cookie_name) {
        WARNING("wrong or missing backend.cookie_name, using: '", DEFAULT_BACKEND_COOKIE_NAME, "'");
        return DEFAULT_BACKEND_COOKIE_NAME;
    }

    return backend_cookie_name.value();
}

string ConfigParser::LogLevel() {
    auto all_log_level = property_tree_.get_optional<string>("all.log_level");

    if (!all_log_level) {
        WARNING("wrong or missing all.log_level, using: '", DEFAULT_LOG_LEVEL, "'");
        return DEFAULT_LOG_LEVEL;
    }

    return all_log_level.value();
}

bool ConfigParser::ConfigValid() {
    return config_valid_;
}

bool ConfigParser::BackendInsertCookie() {
    auto backend_insert_cookie = property_tree_.get_optional<bool>("backend.insert_cookie");

    if (!backend_insert_cookie) {
        WARNING("wrong or missing backend.insert_cookie, using: '", DEFAULT_BACKEND_INSERT_COOKIE, "'");
        return DEFAULT_BACKEND_INSERT_COOKIE;
    }

    return backend_insert_cookie.value();
}

std::string ConfigParser::LogFilePath() {
    auto all_file_path = property_tree_.get_optional<string>("all.log_file_path");

    if (!all_file_path) {
        WARNING("wrong or missing all.log_file_path, using: '", DEFAULT_LOG_FILE_PATH, "'");
        return DEFAULT_LOG_FILE_PATH;
    }

    return all_file_path.value();
}


