//
// Created by morfeush22 on 25.02.19.
//

#include "../include/CLIArgsParser.h"
#include <exception>
#include <iostream>
#include <string>

namespace opts = boost::program_options;
using namespace std;


CLIArgsParser::CLIArgsParser() {
    description_ = make_unique<opts::options_description>("Allowed options");
    variables_map_ = make_unique<opts::variables_map>();

    description_->add_options()
            ("help", "produce help message")
            ("config_file_path", opts::value<string>(), "set path to config file");
}

void CLIArgsParser::ParseCLIArgs(int argc, char **argv) {
    try {
        opts::store(opts::parse_command_line(argc, argv, *description_), *variables_map_);
        opts::notify(*variables_map_);

        if (variables_map_->count("help"))
            return;

        if (!variables_map_->count("config_file_path"))
            return;

        args_valid_ = true;
    }
    catch (exception &e) {
        cerr << "error: " << e.what() << "\n";
    }
    catch (...) {
        cerr << "Exception of unknown type!\n";
    }
}

void CLIArgsParser::ShowHelp() {
    cout << *description_ << "\n";
}

bool CLIArgsParser::ArgsValid() {
    return args_valid_;
}

string CLIArgsParser::GetConfigFilePath() {
    auto config_file_path = (*variables_map_)["config_file_path"];
    return config_file_path.as<string>();
}
