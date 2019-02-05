#ifndef PATH_H
#define PATH_H

#include <filesystem>
namespace fs = std::filesystem;

class Path {

public:
  // Default constructor, null path
  Path();
  // Main constructor, requires string path
  Path(std::string _path);
  // Returns true if path is file, false if directory
  inline bool IsFile() const { return isFile; }
  // Returns absolute path
  inline fs::path Absolute() const { return abs_path; }
  // Returns relative path
  inline fs::path Relative() const { return rel_path; }

private:
  bool isFile;
  fs::path abs_path;
  fs::path rel_path;

};

#endif
