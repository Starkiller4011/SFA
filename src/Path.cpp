#include "SFA/Path.hpp"

// Default null path constructor
Path::Path() {
}

// Path constructor from string path
Path::Path(std::string _path) {
    // Create filesystem path from passed string path
    fs::path passed_path = fs::path(_path);
    // Check if passed path is relative or absolute
    if(passed_path.is_absolute()) {
        // If absolute, set relative path
        abs_path = passed_path;
        rel_path = fs::relative(passed_path, fs::current_path());
    } else if(passed_path.is_relative()) {
        // If relative set absolute path
        rel_path = passed_path;
        abs_path = fs::absolute(rel_path);
    }
    // Check if path is directory or file
    if(!fs::is_directory(passed_path)) {
        isFile = true;
    } else {
        isFile = false;
    }
}
