#include "include/CLIArgsParser.h"
#include "include/ConfigParser.h"
#include "include/HealthChecker.h"
#include "include/HealthCheckerFactory.h"
#include "include/ServersRepository.h"
#include "include/ProxyConnectionFactory.h"
#include "include/LoadBalancer.h"
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

    auto servers = config_parser->BackendServers();
    for (auto &server: servers) {
        std::cout << server;
    }

    boost::asio::io_context io_context;

    auto health_checker_factory = std::make_unique<HealthCheckerFactory>(io_context, config_parser);
    auto servers_repository = std::make_shared<ServersRepository>(std::move(health_checker_factory), config_parser);
    auto proxy_connection_factory = std::make_unique<ProxyConnectionFactory>(io_context, config_parser, servers_repository);
    auto load_balancer = std::make_shared<LoadBalancer>(io_context, config_parser, move(proxy_connection_factory));

    auto deadline_timer = boost::asio::deadline_timer(io_context, boost::posix_time::seconds(1));
    std::function<void(const boost::system::error_code&)> lambda;
    lambda = [&deadline_timer, &servers_repository, &lambda] (const boost::system::error_code&) {
        for (const auto &server: servers_repository->GetAllServers()) {
            std::cout << server;
        }
        deadline_timer.expires_from_now(boost::posix_time::seconds(1));
        deadline_timer.async_wait(lambda);
    };
    deadline_timer.async_wait(lambda);

    io_context.run();

    return 0;
}
