#ifndef ZODIAC_HPP
#define ZODIAC_HPP

#include "consts.hpp"

class Zodiac {

public:
    Zodiac(
        double jd, 
        double lat, 
        double lon, 
        char hsys, 
        str zodiac, 
        int ayanamsha
    );
    void getPatterns(
        Results& results, 
        Sheets& sheets, 
        Selections& selections
    );
    
private:
    double jd;
    double lat;
    double lon;
    char hsys;
    str zodiac;
    int ayanamsha;
    double diff;
    Planet getPlanet(
        str name, 
        double cusps[13], 
        dict<str, str>& traditional, 
        dict<str, str>& modern, 
        int i
    );
    str getPlanetHouse(
        double degree, 
        double cusps[13], 
        dict<str, str>& traditional, 
        dict<str, str>& modern, 
        int i
    );
};

#endif // ZODIAC_HPP

