#include "include/CLIArgsParser.h"
#include <boost/move/unique_ptr.hpp>

namespace pointer = boost::movelib;


int main(int argc, char **argv) {
    auto cliArgsParser = pointer::unique_ptr<CLIArgsParser>(new CLIArgsParser());
    cliArgsParser->ParseCLIArgs(argc, argv);

    if (! cliArgsParser->AreArgsValid()) {
        cliArgsParser->ShowHelp();
        return 1;
    }


    return 0;
}
