#include "../include/utils.hpp"
#include "../include/zodiac.hpp"

extern "C" {
#include "../lib/swe/swephexp.h"
}

Zodiac::Zodiac(
    double jd,
    double lat,
    double lon,
    char hsys,
    str zodiac,
    int ayanamsha
) : jd(jd), lat(lat), lon(lon), hsys(hsys), zodiac(zodiac), ayanamsha(ayanamsha)
{
    if (zodiac == "Sidereal") {
        swe_set_sid_mode(ayanamsha, 0, 0);
        diff = swe_get_ayanamsa(jd);
    } else {
        diff = 0;
    }
}

str Zodiac::getPlanetHouse(
    double degree, 
    double cusps[13], 
    dict<str, str>& traditional, 
    dict<str, str>& modern, 
    int i
) {
    str self;
    int index;
    double cur, pre;
    dict<str, str> attrs;
    for (int j = 0; j < 12; j++) {
        index = j ? j - 1 : 11;
        pre = cusps[index + 1] - diff;
        cur = cusps[j + 1] - diff;
        if (
            (pre < degree && degree < cur) ||
            (pre > cur && cur > degree) ||
            (degree > pre && pre > cur)
        )
        {
            self = "House-" + std::to_string(index + 1);
        }
        if (!i) {
            attrs = getAttrs(cur);
            traditional[LORDS[j]] = \
                TRADITIONAL_RULERSHIP -> data[attrs["sign"]];
            modern[LORDS[j]] = MODERN_RULERSHIP -> data[attrs["sign"]];
        }
    }
    return self;
}

Planet Zodiac::getPlanet(
    str name, 
    double cusps[13], 
    dict<str, str>& traditional, 
    dict<str, str>& modern, 
    int i
) {
    Planet planet;
    double x2[6];
    char serr[256];
    swe_calc_ut(
        jd,
        PLANETS -> data[name],
        SEFLG_SPEED,
        x2,
        serr
    );
    planet.name = name;
    planet.degree = x2[0] - diff;
    planet.sign = SIGNS[(int)(planet.degree / 30)];
    planet.house = getPlanetHouse(
        planet.degree, 
        cusps, 
        traditional, 
        modern, 
        i
    );
    return planet;
}

void Zodiac::getPatterns(
    Results& results, 
    Sheets& sheets, 
    Selections& selections
) {
    swe_set_ephe_path("../eph");
    double cusps[13];
    double ascmc[10];
    dict<str, str> attrs, traditional, modern;
    swe_houses(jd, lat, lon, hsys, cusps, ascmc);
    list<Planet> planets, planets2, planets3, planets4;
    Planet planet, other;
    str aspect, aspect1, aspect2, aspect3, aspect4;
    str m_lord, t_lord, p1, p2, p3, p4;
    double d1, d2, d3, d4, midpoint;
    list<double> degrees;
    list<str> aspects;
    for (int i = 0; i < 15; i++) {
        if (PLANETS -> keys[i] == "ASC") {
            planet.name = "ASC";
            planet.degree = cusps[1];
            planet.sign = SIGNS[(int)(planet.degree / 30)];
            planet.house = "House-1";
        }
        else if (PLANETS -> keys[i] == "MC") {
            planet.name = "MC";
            planet.degree = cusps[10];
            planet.sign = SIGNS[(int)(planet.degree / 30)];
            planet.house = "House-10";
        }
        else {
            planet = getPlanet(
                PLANETS -> keys[i], 
                cusps, 
                traditional, 
                modern, 
                i
            );
            attrs = getAttrs(planet.degree);
            if (sheets.planets_in_signs) {
                results.planets_in_signs\
                    [planet.name][attrs["sign"]]++;
            }
            if (sheets.planets_in_elements) {
                results.planets_in_elements\
                    [planet.name][attrs["element"]]++;
            }
            if (sheets.planets_in_modes) {
                results.planets_in_modes\
                    [planet.name][attrs["mode"]]++;
            }
            if (sheets.planets_in_houses) {
                results.planets_in_houses\
                    [planet.name][planet.house]++;
            }
            if (sheets.planets_in_houses_in_signs) {
                results.planets_in_houses_in_signs\
                    [planet.name][planet.house][planet.sign]++;
            }
        }
        if (i < 12) {
            attrs = getAttrs(cusps[i + 1]);
            if (sheets.houses_in_signs) {
                results.houses_in_signs[HOUSES[i]][attrs["sign"]]++;
            }
            if (sheets.houses_in_elements) {
                results.houses_in_elements[HOUSES[i]][attrs["element"]]++;
            }
            if (sheets.houses_in_modes) {
                results.houses_in_modes[HOUSES[i]][attrs["mode"]]++;
            }
        }
        if (
            sheets.basic_modern_rulership ||
            sheets.basic_traditional_rulership ||
            sheets.detailed_traditional_rulership ||
            sheets.detailed_modern_rulership ||
            sheets.sum_of_aspects ||
            sheets.aspects
        ) {
            for (int j = 0; j < 14; j++) {
                if (j < i) {
                    other = planets[j];
                    aspect = findAspect(
                        other.degree, 
                        planet.degree, 
                        selections.aspects, 
                        "orb1"
                    );
                    if (aspect != "") {
                        if (sheets.aspects) {
                            results.aspects[other.name][aspect][planet.name]++;
                        }
                        if (sheets.sum_of_aspects) {
                            results.sum_of_aspects[other.name][planet.name]++;
                        }
                    }
                }
                if (j < 12) {
                    t_lord = traditional[LORDS[j]];
                    m_lord = modern[LORDS[j]];
                    if (planet.name == split(t_lord, " (")[0] &&
                        (
                            sheets.basic_traditional_rulership ||
                            sheets.detailed_traditional_rulership
                        )
                    )
                    {
                        if (sheets.basic_traditional_rulership) {
                            results.basic_traditional_rulership\
                                [LORDS[j]][planet.house]++;
                        }
                        if (sheets.detailed_traditional_rulership) {
                            results.detailed_traditional_rulership\
                                [LORDS[j]][t_lord][planet.house]++;
                        }
                    }
                    if (planet.name == split(m_lord, " (")[0] &&
                        (
                            sheets.basic_modern_rulership ||
                            sheets.detailed_modern_rulership
                        )
                    )
                    {
                        if (sheets.basic_modern_rulership) {
                            results.basic_modern_rulership\
                                [LORDS[j]][planet.house]++;
                        }
                        if (sheets.detailed_modern_rulership) {
                            results.detailed_modern_rulership\
                                [LORDS[j]][m_lord][planet.house]++;
                        }
                    }
                }
            }
        }
        planets.push_back(planet);
    }
    if (
        sheets.midpoints ||
        sheets.t_square ||
        sheets.grand_trine ||
        sheets.yod ||
        sheets.grand_cross ||
        sheets.kite ||
        sheets.mystic_rectangle
    ) {
        for (int i = 0; i < 15; i++) {
            planets2 = pop(planets, i);
            for (int j = 0; j < 14; j++) {
                planets3 = pop(planets2, j);
                for (int k = 0; k < 13; k++) {
                    planets4 = pop(planets3, k);
                    if (sheets.midpoints && j >= i) {
                        p1 = planets[i].name;
                        p2 = planets2[j].name;
                        p3 = planets3[k].name;
                        d1 = planets[i].degree;
                        d2 = planets2[j].degree;
                        d3 = planets3[k].degree;
                        midpoint = findMidpoint(d1, d2);
                        aspect = findAspect(
                            midpoint,
                            d3,
                            selections.aspects,
                            "orb2"
                            );
                        if (aspect != "") {
                            results.midpoints[p1][p2][aspect][p3]++;
                        }
                    }
                    if (
                        (
                            sheets.t_square ||
                            sheets.grand_trine ||
                            sheets.yod
                            ) &&
                        k >= j
                        ) {
                        p1 = planets[i].name;
                        p2 = planets2[j].name;
                        p3 = planets3[k].name;
                        d1 = planets[i].degree;
                        d2 = planets2[j].degree;
                        d3 = planets3[k].degree;
                        aspect1 = findAspect(
                            d1, d2, selections.aspects, "orb1"
                        );
                        aspect2 = findAspect(
                            d2, d3, selections.aspects, "orb1"
                        );
                        aspect3 = findAspect(
                            d3, d1, selections.aspects, "orb1"
                        );
                        aspects = {aspect1, aspect2, aspect3};
                        if (sheets.t_square && aspects == T_SQUARE) {
                            results.t_square[p1][p2][p3]++;
                        }
                        if (sheets.grand_trine && aspects == GRAND_TRINE) {
                            results.grand_trine[p1][p2][p3]++;
                        }
                        if (sheets.yod && aspects == YOD) {
                            results.yod[p1][p2][p3]++;
                        }
                    }
                    if (
                        sheets.grand_cross ||
                        sheets.kite ||
                        sheets.mystic_rectangle
                        ) {
                        for (int m = 0; m < 12; m++) {
                            if (m >= k) {
                                p1 = planets[i].name;
                                p2 = planets2[j].name;
                                p3 = planets3[k].name;
                                p4 = planets4[m].name;
                                d1 = planets[i].degree;
                                d2 = planets2[j].degree;
                                d3 = planets3[k].degree;
                                d4 = planets4[m].degree;
                                aspect1 = findAspect(
                                    d1, d2, selections.aspects, "orb1"
                                );
                                aspect2 = findAspect(
                                    d2, d3, selections.aspects, "orb1"
                                );
                                aspect3 = findAspect(
                                    d3, d4, selections.aspects, "orb1"
                                );
                                aspect4 = findAspect(
                                    d4, d1, selections.aspects, "orb1"
                                );
                                aspects = {
                                    aspect1, aspect2, aspect3, aspect4
                                };
                                if (
                                    sheets.grand_cross && 
                                    aspects == GRAND_CROSS
                                ) {
                                    results.grand_cross[p1][p2][p3][p4]++;
                                }
                                if (sheets.kite && aspects == KITE) {
                                    results.kite[p1][p2][p3][p4]++;
                                }
                                if (
                                    sheets.mystic_rectangle && 
                                    aspects == MYSTIC_RECTANGLE
                                ) {
                                    results.mystic_rectangle[p1][p2][p3][p4]++;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
