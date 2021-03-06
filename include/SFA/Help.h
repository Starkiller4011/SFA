#ifndef HELP_H
#define HELP_H

#include <iostream>
#include <fstream>
#include <string>

static std::string VERSION = "0.9.9";

static void PrintHelp() {
    // inform user of usage and exit
    std::cout << "SFA " << VERSION << " - Usage: sfa [options] input_file" << std::endl;
    exit(1);
}

#endif