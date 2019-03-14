//
// Created by morfeush22 on 25.02.19.
//

#ifndef LOAD_BALANCER_CLIARGSPARSER_H
#define LOAD_BALANCER_CLIARGSPARSER_H

#include <boost/program_options.hpp>
#include <memory>


class CLIArgsParser {

public:
    /**
     * Parses command line arguments. Provides command line help dialog.
     */
    CLIArgsParser();

    /**
     * Sets internal structures for command line parsing.
     * @param argc Number of command line arguments
     * @param argv Pointer to array of passed arguments
     */
    void ParseCLIArgs(int argc, char **argv);

    /**
     * Prints help dialog to stdout.
     */
    void ShowHelp();

    /**
     * Gets status of passed command line arguments.
     * @return Boolean that indicates if passed arguments are valid
     */
    bool ArgsValid();

    /**
     * Gets value of --config_file_path. Must be called after ArgsValid().
     * @return Value of --config_file_path
     */
    std::string GetConfigFilePath();

private:
    bool args_valid_ = false;
    std::unique_ptr<boost::program_options::options_description> description_;
    std::unique_ptr<boost::program_options::variables_map> variables_map_;

};


#endif //LOAD_BALANCER_CLIARGSPARSER_H
