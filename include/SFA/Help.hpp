#ifndef HELP_H
#define HELP_H

#include <iostream>
#include <fstream>
#include <string>

// Get version string
static std::string Version() {
    std::ifstream vFile;
    vFile.open("/usr/share/sfa/VERSION");
    std::string version;
    vFile >> version;
    vFile.close();
    return version;
}

#endif