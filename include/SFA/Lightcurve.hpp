#ifndef LIGHTCURVE_H
#define LIGHTCURVE_H

#include "Collections.hpp"

class Lightcurve {

public:
    Lightcurve();
    void SetDelimiter(std::string _delimiter);

private:
    void LoadData();

private:
    bool usesDelimiter; // Not currently implemented
    std::string delimiter; // TODO - implement delimiter usage
    Path inputPath;
    List<double> timeCol;
    List<double> valueCol;

};

#endif
