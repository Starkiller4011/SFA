#include "Path.h"

#include <string>
#include <unistd.h>
#include <limits.h>

Path::Path(std::string _path) {
    m_CWD = getCWD();
}

std::string Path::getCWD() {
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    return std::string(result,(count>0)?count:0);
}