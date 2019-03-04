#include "include/CLIArgsParser.h"
#include "include/ConfigParser.h"
#include "include/HealthChecker.h"
#include "include/HealthCheckerFactory.h"
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

    auto health_checker_factory = std::make_unique<HealthCheckerFactory>(io_context, config_parser);

    auto health_checker = health_checker_factory->MakeHealthChecker();
    health_checker->run("localhost", "8080");

    auto deadline_timer = boost::asio::deadline_timer(io_context, boost::posix_time::seconds(1));
    std::function<void(const boost::system::error_code&)> lambda;
    lambda = [&deadline_timer, &health_checker, &lambda] (const boost::system::error_code&) {
        std::cout << health_checker->healthy() << "\n";
        deadline_timer.expires_from_now(boost::posix_time::seconds(1));
        deadline_timer.async_wait(lambda);
    };
    deadline_timer.async_wait(lambda);

    auto servers = config_parser->BackendServers();
    for (auto &server: servers) {
        std::cout << server;
    }

    io_context.run();

    return 0;
}
