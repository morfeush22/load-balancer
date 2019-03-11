#include "include/BackendServersRepository.h"
#include "include/CLIArgsParser.h"
#include "include/ConfigParser.h"
#include "include/FrontendServer.h"
#include "include/HealthChecker.h"
#include "include/HealthCheckerFactory.h"
#include "include/Logger.h"
#include "include/ProxyConnectionFactory.h"
#include "include/RoundRobin.h"
#include "include/SchedulingStrategyBuilder.h"
#include <memory>

using namespace std;


int main(int argc, char **argv) {
    auto cli_args_parser = make_unique<CLIArgsParser>();
    cli_args_parser->ParseCLIArgs(argc, argv);

    if (!cli_args_parser->ArgsValid()) {
        cli_args_parser->ShowHelp();
        return EXIT_FAILURE;
    }

    auto config_file_path = cli_args_parser->GetConfigFilePath();
    auto config_parser = make_shared<ConfigParser>(config_file_path);
    config_parser->ParseConfigFile();

    if (!config_parser->ConfigValid()) {
        ERROR("invalid config file");
        return EXIT_FAILURE;
    }

    SET_LOGGING_LEVEL(config_parser->LogLevel());

    boost::asio::io_context io_context;

    auto health_checker_factory = make_unique<HealthCheckerFactory>(io_context, config_parser);
    auto backend_servers_repository = make_shared<BackendServersRepository>(
            move(health_checker_factory),
            config_parser);

    auto scheduling_strategy_builder = make_unique<SchedulingStrategyBuilder>(config_parser);
    auto scheduling_strategy = scheduling_strategy_builder->ConstructSchedulingStrategy();

    auto proxy_connection_factory = make_unique<ProxyConnectionFactory>(
            io_context,
            backend_servers_repository,
            scheduling_strategy,
            config_parser);
    auto frontend_server = make_shared<FrontendServer>(io_context, move(proxy_connection_factory), config_parser);

    frontend_server->run();
    io_context.run();

    return EXIT_SUCCESS;
}
