//
// Created by morfeush22 on 25.02.19.
//

#include "../include/CLIArgsParser.h"
#include <exception>
#include <iostream>
#include <string>

namespace opts = boost::program_options;
namespace pointer = boost::movelib;


CLIArgsParser::CLIArgsParser() {
    _description = pointer::unique_ptr<opts::options_description>(new opts::options_description("Allowed options"));
    _variables_map = pointer::unique_ptr<opts::variables_map>(new opts::variables_map());

    _description->add_options()
            ("help", "produce help message")
            ("config_file_path", opts::value<std::string>(), "set path to config file");
}

void CLIArgsParser::ParseCLIArgs(int argc, char **argv) {
    try {
        opts::store(opts::parse_command_line(argc, argv, *_description), *_variables_map);
        opts::notify(*_variables_map);

        if (_variables_map->count("help"))
            return;

        if (!_variables_map->count("config_file_path"))
            return;

        _are_args_valid = true;
    }
    catch(std::exception &e) {
        std::cerr << "error: " << e.what() << "\n";
    }
    catch(...) {
        std::cerr << "Exception of unknown type!\n";
    }
}

void CLIArgsParser::ShowHelp() {
    std::cout << *_description << "\n";
}

bool CLIArgsParser::AreArgsValid() {
    return _are_args_valid;
}

std::string CLIArgsParser::GetConfigFilePath() {
    auto config_file_path = (*_variables_map)["config_file_path"];
    return config_file_path.as<std::string>();
}
