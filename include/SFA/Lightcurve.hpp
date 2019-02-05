#ifndef LIGHTCURVE_H
#define LIGHTCURVE_H

#include "SFA/Collections.hpp"

class Lightcurve {

public:
    Lightcurve(Path _path);
    void SetDelimiter(std::string _delimiter);
    void LoadData();
    inline List<double> TimeCol() const { return timeCol; }
    inline List<double> ValueCol() const { return valueCol; }

private:

private:
    bool usesDelimiter; // Not currently implemented
    std::string delimiter; // TODO - implement delimiter usage
    Path datafilePath;
    List<double> timeCol;
    List<double> valueCol;

};

#endif
