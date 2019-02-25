//
// Created by morfeush22 on 25.02.19.
//

#ifndef LOAD_BALANCER_CLIARGSPARSER_H
#define LOAD_BALANCER_CLIARGSPARSER_H

#include <boost/move/unique_ptr.hpp>
#include <boost/program_options.hpp>


class CLIArgsParser {

    public:
    CLIArgsParser();
    void ParseCLIArgs(int argc, char **argv);
    void ShowHelp();
    bool AreArgsValid();
    std::string GetConfigFilePath();

    private:
    boost::movelib::unique_ptr<boost::program_options::options_description> _description;
    boost::movelib::unique_ptr<boost::program_options::variables_map> _variables_map;
    bool _are_args_valid = false;

};


#endif //LOAD_BALANCER_CLIARGSPARSER_H
