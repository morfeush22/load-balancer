//
// Created by morfeush22 on 25.02.19.
//

#include "../include/ConfigParser.h"
#include <boost/property_tree/ini_parser.hpp>

namespace prop_tree = boost::property_tree;


ConfigParser::ConfigParser(std::string config_file_path) {
    _config_file_path = config_file_path;
}

void ConfigParser::ParseConfigFile() {
    prop_tree::ini_parser::read_ini(_config_file_path, _property_tree);
}


