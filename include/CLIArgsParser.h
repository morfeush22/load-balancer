//
// Created by morfeush22 on 25.02.19.
//

#ifndef LOAD_BALANCER_CLIARGSPARSER_H
#define LOAD_BALANCER_CLIARGSPARSER_H

#include <boost/program_options.hpp>
#include <memory>


class CLIArgsParser {

    public:
    CLIArgsParser();
    void ParseCLIArgs(int argc, char **argv);
    void ShowHelp();
    bool ArgsValid();
    std::string GetConfigFilePath();

    private:
    std::unique_ptr<boost::program_options::options_description> _description;
    std::unique_ptr<boost::program_options::variables_map> _variables_map;
    bool _are_args_valid = false;

};


#endif //LOAD_BALANCER_CLIARGSPARSER_H
