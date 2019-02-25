#include "include/CLIArgsParser.h"
#include "include/ConfigParser.h"
#include <boost/move/unique_ptr.hpp>

namespace ptr = boost::movelib;


int main(int argc, char **argv) {
    auto cliArgsParser = ptr::unique_ptr<CLIArgsParser>(new CLIArgsParser());
    cliArgsParser->ParseCLIArgs(argc, argv);

    if (! cliArgsParser->AreArgsValid()) {
        cliArgsParser->ShowHelp();
        return 1;
    }

    auto config_file_path = cliArgsParser->GetConfigFilePath();
    auto configParser = ptr::unique_ptr<ConfigParser>(new ConfigParser(config_file_path));
    configParser->ParseConfigFile();

    return 0;
}
