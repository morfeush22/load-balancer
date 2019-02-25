// Copyright Vladimir Prus 2002-2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

/* The simplest usage of the library.
 */

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
