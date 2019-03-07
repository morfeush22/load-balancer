#include "include/CLIArgsParser.h"
#include "include/ConfigParser.h"
#include "include/HealthChecker.h"
#include "include/HealthCheckerFactory.h"
#include "include/BackendServersRepository.h"
#include "include/ProxyConnectionFactory.h"
#include "include/FrontendServer.h"
#include "include/Logger.h"
#include "include/RoundRobin.h"
#include "include/SchedulingStrategyBuilder.h"
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
    //TODO IsConfigValid
    config_parser->ParseConfigFile();

    SET_LOGGING_LEVEL(config_parser->LogLevel());

    boost::asio::io_context io_context;

    auto scheduling_strategy_builder = std::make_unique<SchedulingStrategyBuilder>(config_parser);
    auto strategy = scheduling_strategy_builder->ConstructStrategy();

    auto health_checker_factory = std::make_unique<HealthCheckerFactory>(io_context, config_parser);
    auto servers_repository = std::make_shared<BackendServersRepository>(std::move(health_checker_factory), config_parser);
    auto proxy_connection_factory = std::make_unique<ProxyConnectionFactory>(io_context, config_parser, servers_repository, strategy);
    auto load_balancer = std::make_shared<FrontendServer>(io_context, config_parser, move(proxy_connection_factory));

    load_balancer->run();
    io_context.run();

    return 0;
}
