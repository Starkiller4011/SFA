#ifndef LIGHTCURVE_H
#define LIGHTCURVE_H

#include <vector>

namespace sfa {

class Lightcurve {

public:
    Lightcurve(Path _path);
    void SetDelimiter(std::string _delimiter);
    void LoadData();
    inline std::vector<double> TimeCol() const { return timeCol; }
    inline std::vector<double> ValueCol() const { return valueCol; }

private:
    bool usesDelimiter; // Not currently implemented
    std::string delimiter; // TODO - implement delimiter usage
    Path datafilePath;
    std::vector<double> timeCol;
    std::vector<double> valueCol;

};

}

#endif
