#ifndef PATH_H
#define PATH_H

#include <string>

class Path {

public:
  Path(std::string _path);
  inline std::string CWD() const { return m_CWD; }
  inline std::string AbsolutePath() const { return absolutePath; }

private:
  std::string getCWD();

private:
  std::string absolutePath;
  std::string m_CWD;

};

#endif
