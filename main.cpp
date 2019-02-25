#include "include/CLIArgsParser.h"
#include "include/ConfigParser.h"
#include <memory>


int main(int argc, char **argv) {
    auto cliArgsParser = std::make_unique<CLIArgsParser>();
    cliArgsParser->ParseCLIArgs(argc, argv);

    if (! cliArgsParser->AreArgsValid()) {
        cliArgsParser->ShowHelp();
        return 1;
    }

    auto config_file_path = cliArgsParser->GetConfigFilePath();
    auto configParser = std::make_unique<ConfigParser>(config_file_path);
    configParser->ParseConfigFile();

    return 0;
}
