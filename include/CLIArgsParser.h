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
    bool args_valid_ = false;
    std::unique_ptr<boost::program_options::options_description> description_;
    std::unique_ptr<boost::program_options::variables_map> variables_map_;

};


#endif //LOAD_BALANCER_CLIARGSPARSER_H
