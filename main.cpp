#include "include/CLIArgsParser.h"
#include "include/ConfigParser.h"
#include "include/HealthChecker.h"
#include <memory>


int main(int argc, char **argv) {
    auto cli_args_parser = std::make_unique<CLIArgsParser>();
    cli_args_parser->ParseCLIArgs(argc, argv);

    if (! cli_args_parser->ArgsValid()) {
        cli_args_parser->ShowHelp();
        return 1;
    }

    auto config_file_path = cli_args_parser->GetConfigFilePath();
    auto config_parser = std::make_shared<ConfigParser>(config_file_path);
    config_parser->ParseConfigFile();

    boost::asio::io_context io_context;

    auto health_checker = std::make_shared<HealthChecker>(io_context, config_parser);
    health_checker->run("localhost", "8080", "/");

    io_context.run();

    return 0;
}
