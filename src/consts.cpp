#include "../include/consts.hpp"

Dict<str, dict<str, double>> *ASPECTS = new Dict<str, dict<str, double>>();
Dict<str, int> *PLANETS = new Dict<str, int>();
Dict<str, dict<str, int>> *AYANAMSHA = new Dict<str, dict<str, int>>();
Dict<str, dict<str, int>> *HOUSE_SYSTEMS = new Dict<str, dict<str, int>>();
Dict<str, int> *SHEETS = new Dict<str, int>();
Dict<str, int> *ATTRIBUTES = new Dict<str, int>();
Dict<str, int> *RODDEN_RATINGS = new Dict<str, int>();
Dict<str, dict<str, double>> *RANGES = new Dict<str, dict<str, double>>();
Dict<str, str> *TRADITIONAL_RULERSHIP = new Dict<str, str>();
Dict<str, str> *MODERN_RULERSHIP = new Dict<str, str>();
list<str> SIGNS;
list<str> ELEMENTS;
list<str> MODES;
list<str> HOUSES;
list<str> LORDS;
list<str> CALC_TYPES;
list<str> ZODIAC;
list<str> OPTIONAL_SELECTIONS;
list<spinBoxMap> RANGE_VALUES;
list<str> DB_COLUMNS;
str ADB_VERSION;
str VERSION = "1.0.0";
Dict<str, str> *ABOUT_COLUMNS = new Dict<str, str>();
list<str> T_SQUARE;
list<str> GRAND_TRINE;
list<str> YOD;
list<str> GRAND_CROSS;
list<str> KITE;
list<str> MYSTIC_RECTANGLE;

void init_ASPECTS() {
    insert<str, dict<str, double>>(
        ASPECTS, 
        "Conjunction", 
        dict<str, double>{{"degree", 0}, {"orb1", 10}, {"orb2", 2}}
    );
    insert<str, dict<str, double>>(
        ASPECTS,
        "Semi-Sextile",
        dict<str, double>{{"degree", 30}, {"orb1", 3}, {"orb2", 1}}
    );
    insert<str, dict<str, double>>(
        ASPECTS, 
        "Semi-Square", 
        dict<str, double>{{"degree", 45}, {"orb1", 3}, {"orb2", 1.5}}
    );
    insert<str, dict<str, double>>(
        ASPECTS, 
        "Sextile", 
        dict<str, double>{{"degree", 60}, {"orb1", 6}, {"orb2", 1}}
    );
    insert<str, dict<str, double>>(
        ASPECTS, 
        "Quintile", 
        dict<str, double>{{"degree", 72}, {"orb1", 2}, {"orb2", 1}}
    );
    insert<str, dict<str, double>>(
        ASPECTS, 
        "Square", 
        dict<str, double>{{"degree", 90}, {"orb1", 10}, {"orb2", 2}}
    );
    insert<str, dict<str, double>>(
        ASPECTS, 
        "Trine", 
        dict<str, double>{{"degree", 120}, {"orb1", 10}, {"orb2", 1}}
    );
    insert<str, dict<str, double>>(
        ASPECTS, 
        "Sesquiquadrate", 
        dict<str, double>{{"degree", 135}, {"orb1", 3}, {"orb2", 1.5}}
    );
    insert<str, dict<str, double>>(
        ASPECTS, 
        "BiQuintile", 
        dict<str, double>{{"degree", 144}, {"orb1", 2}, {"orb2", 1}}
    );
    insert<str, dict<str, double>>(
        ASPECTS, 
        "Quincunx", 
        dict<str, double>{{"degree", 150}, {"orb1", 3}, {"orb2", 1}}
    );
    insert<str, dict<str, double>>(
        ASPECTS, 
        "Opposite", 
        dict<str, double>{{"degree", 180}, {"orb1", 10}, {"orb2", 2}}
    );
}

void init_PLANETS() {
    insert<str, int>(PLANETS, "Sun", 0);
    insert<str, int>(PLANETS, "Moon", 1);
    insert<str, int>(PLANETS, "Mercury", 2);
    insert<str, int>(PLANETS, "Venus", 3);
    insert<str, int>(PLANETS, "Mars", 4);
    insert<str, int>(PLANETS, "Jupiter", 5);
    insert<str, int>(PLANETS, "Saturn", 6);
    insert<str, int>(PLANETS, "Uranus", 7);
    insert<str, int>(PLANETS, "Neptune", 7);
    insert<str, int>(PLANETS, "Pluto", 9);
    insert<str, int>(PLANETS, "Mean Node", 11);
    insert<str, int>(PLANETS, "True Node", 10);
    insert<str, int>(PLANETS, "Chiron", 15);
    insert<str, int>(PLANETS, "ASC", -1);
    insert<str, int>(PLANETS, "MC", -1);
}

void init_AYANAMSHA() {
    insert<str, dict<str, int>>(
        AYANAMSHA, 
        "Aldebaran 15 Taurus", 
        dict<str, int>{{"value", 14}, {"default", 0}}
    );
    insert<str, dict<str, int>>(
        AYANAMSHA, 
        "Aryabhata", 
        dict<str, int>{{"value", 23}, {"default", 0}}
    );
    insert<str, dict<str, int>>(
        AYANAMSHA, 
        "Aryabhata (Mean Sun)", 
        dict<str, int>{{"value", 24}, {"default", 0}}
    );
    insert<str, dict<str, int>>(
        AYANAMSHA, 
        "B1950", 
        dict<str, int>{{"value", 20}, {"default", 0}}
    );
    insert<str, dict<str, int>>(
        AYANAMSHA, 
        "Babylonian (Huber)", 
        dict<str, int>{{"value", 12}, {"default", 0}}
    );
    insert<str, dict<str, int>>(
        AYANAMSHA, 
        "Babylonian (Kugler 1)", 
        dict<str, int>{{"value", 9}, {"default", 0}}
    );
    insert<str, dict<str, int>>(
        AYANAMSHA, 
        "Babylonian (Kugler 2)", 
        dict<str, int>{{"value", 10}, {"default", 0}}
    );
    insert<str, dict<str, int>>(
        AYANAMSHA, 
        "Babylonian (Kugler 3)", 
        dict<str, int>{{"value", 11}, {"default", 0}}
    );
    insert<str, dict<str, int>>(
        AYANAMSHA, 
        "De Luce", 
        dict<str, int>{{"value", 2}, {"default", 0}}
    );
    insert<str, dict<str, int>>(
        AYANAMSHA, 
        "Fagan-Bradley", 
        dict<str, int>{{"value", 0}, {"default", 0}}
    );
    insert<str, dict<str, int>>(
        AYANAMSHA, 
        "Galactic Center 0 Sagittarius", 
        dict<str, int>{{"value", 17}, {"default", 0}}
    );
    insert<str, dict<str, int>>(
        AYANAMSHA, 
        "Hindu-Lahiri", 
        dict<str, int>{{"value", 1}, {"default", 1}}
    );
    insert<str, dict<str, int>>(
        AYANAMSHA, 
        "Hipparchus", 
        dict<str, int>{{"value", 15}, {"default", 0}}
    );
    insert<str, dict<str, int>>(
        AYANAMSHA, 
        "J1900", 
        dict<str, int>{{"value", 19}, {"default", 0}}
    );
    insert<str, dict<str, int>>(
        AYANAMSHA, 
        "J2000", 
        dict<str, int>{{"value", 18}, {"default", 0}}
    );
    insert<str, dict<str, int>>(
        AYANAMSHA, 
        "JN Bhasin", 
        dict<str, int>{{"value", 8}, {"default", 0}}
    );
    insert<str, dict<str, int>>(
        AYANAMSHA, 
        "Krishnamurti", 
        dict<str, int>{{"value", 5}, {"default", 0}}
    );
    insert<str, dict<str, int>>(
        AYANAMSHA, 
        "Raman", 
        dict<str, int>{{"value", 3}, {"default", 0}}
    );
    insert<str, dict<str, int>>(
        AYANAMSHA, 
        "Sassanian", 
        dict<str, int>{{"value", 16}, {"default", 0}}
    );
    insert<str, dict<str, int>>(
        AYANAMSHA, 
        "Suryasiddhanta", 
        dict<str, int>{{"value", 21}, {"default", 0}}
    );
    insert<str, dict<str, int>>(
        AYANAMSHA, 
        "Suryasiddhanta Citra", 
        dict<str, int>{{"value", 26}, {"default", 0}}
    );
    insert<str, dict<str, int>>(
        AYANAMSHA, 
        "Suryasiddhanta Revati", 
        dict<str, int>{{"value", 25}, {"default", 0}}
    );
    insert<str, dict<str, int>>(
        AYANAMSHA, 
        "Suryasiddhanta (Mean Sun)", 
        dict<str, int>{{"value", 22}, {"default", 0}}
    );
    insert<str, dict<str, int>>(
        AYANAMSHA,
        "True Citra", 
        dict<str, int>{{"value", 27}, {"default", 0}}
    );
    insert<str, dict<str, int>>(
        AYANAMSHA, 
        "True Revati", 
        dict<str, int>{{"value", 28}, {"default", 0}}
    );
    insert<str, dict<str, int>>(
        AYANAMSHA, 
        "Usha & Sashi", 
        dict<str, int>{{"value", 4}, {"default", 0}}
    );
    insert<str, dict<str, int>>(
        AYANAMSHA, 
        "Yukteshwar", 
        dict<str, int>{{"value", 7}, {"default", 0}}
    );
}

void init_HOUSE_SYSTEMS() {
    insert<str, dict<str, int>>(
        HOUSE_SYSTEMS, 
        "Placidus", 
        dict<str, int>{{"value", 'P'}, {"default", 1}}
    );
    insert<str, dict<str, int>>(
        HOUSE_SYSTEMS, 
        "Koch", 
        dict<str, int>{{"value", 'K'}, {"default", 0}}
    );
    insert<str, dict<str, int>>(
        HOUSE_SYSTEMS, 
        "Porphyrius", 
        dict<str, int>{{"value", 'O'}, {"default", 0}}
    );
    insert<str, dict<str, int>>(
        HOUSE_SYSTEMS, 
        "Regiomontanus", 
        dict<str, int>{{"value", 'R'}, {"default", 0}}
    );
    insert<str, dict<str, int>>(
        HOUSE_SYSTEMS, 
        "Campanus", 
        dict<str, int>{{"value", 'C'}, {"default", 0}}
    );
    insert<str, dict<str, int>>(
        HOUSE_SYSTEMS, 
        "Equal", 
        dict<str, int>{{"value", 'E'}, {"default", 0}}
    );
    insert<str, dict<str, int>>(
        HOUSE_SYSTEMS, 
        "Whole Signs", 
        dict<str, int>{{"value", 'W'}, {"default", 0}}
    );
}

void init_SHEETS() {
    insert<str, int>(SHEETS, "Info", 0);
    insert<str, int>(SHEETS, "Planets In Signs", 1);
    insert<str, int>(SHEETS, "Planets In Elements", 1);
    insert<str, int>(SHEETS, "Planets In Modes", 1);
    insert<str, int>(SHEETS, "Houses In Signs", 1);
    insert<str, int>(SHEETS, "Houses In Elements", 1);
    insert<str, int>(SHEETS, "Houses In Modes", 1);
    insert<str, int>(SHEETS, "Planets In Houses", 1);
    insert<str, int>(SHEETS, "Planets In Houses In Signs", 1);
    insert<str, int>(SHEETS, "Basic Traditional Rulership", 1);
    insert<str, int>(SHEETS, "Basic Modern Rulership", 1);
    insert<str, int>(SHEETS, "Detailed Traditional Rulership", 1);
    insert<str, int>(SHEETS, "Detailed Modern Rulership", 1);
    insert<str, int>(SHEETS, "Aspects", 1);
    insert<str, int>(SHEETS, "Sum Of Aspects", 1);
    insert<str, int>(SHEETS, "T-Square", 1);
    insert<str, int>(SHEETS, "Grand Trine", 1);
    insert<str, int>(SHEETS, "Yod", 1);
    insert<str, int>(SHEETS, "Grand Cross", 1);
    insert<str, int>(SHEETS, "Kite", 1);
    insert<str, int>(SHEETS, "Mystic Rectangle", 1);
    insert<str, int>(SHEETS, "Midpoints", 1);
}

void init_ATTRIBUTES() {
    insert<str, int>(ATTRIBUTES, "Event", 0);
    insert<str, int>(ATTRIBUTES, "Human", 1);
    insert<str, int>(ATTRIBUTES, "Male", 1);
    insert<str, int>(ATTRIBUTES, "Female", 1);
    insert<str, int>(ATTRIBUTES, "North Hemisphere", 1);
    insert<str, int>(ATTRIBUTES, "South Hemisphere", 1);
    insert<str, int>(ATTRIBUTES, "West Hemisphere", 1);
    insert<str, int>(ATTRIBUTES, "East Hemisphere", 1);
}

void init_RODDEN_RATINGS() {
    insert<str, int>(RODDEN_RATINGS, "AA", 1);
    insert<str, int>(RODDEN_RATINGS, "A", 1);
    insert<str, int>(RODDEN_RATINGS, "B", 1);
    insert<str, int>(RODDEN_RATINGS, "C", 1);
    insert<str, int>(RODDEN_RATINGS, "D", 0);
    insert<str, int>(RODDEN_RATINGS, "X", 0);
    insert<str, int>(RODDEN_RATINGS, "XX", 0);
}

void init_RANGES() {
    insert<str, dict<str, double>>(
        RANGES, 
        "Year",
        dict<str, double>{{"min", 0}, {"max", 0}, {"step", 1}}
    );
    insert<str, dict<str, double>>(
        RANGES, 
        "Latitude",
        dict<str, double>{{"min", 0}, {"max", 0}, {"step", .000001}}
    );
    insert<str, dict<str, double>>(
        RANGES, 
        "Longitude", 
        dict<str, double>{{"min", 0}, {"max", 0}, {"step", .000001}}
    );
}

void init_SIGNS() {
    SIGNS.push_back("Aries");
    SIGNS.push_back("Taurus");
    SIGNS.push_back("Gemini");
    SIGNS.push_back("Cancer");
    SIGNS.push_back("Leo");
    SIGNS.push_back("Virgo");
    SIGNS.push_back("Libra");
    SIGNS.push_back("Scorpio");
    SIGNS.push_back("Sagittarius");
    SIGNS.push_back("Capricorn");
    SIGNS.push_back("Aquarius");
    SIGNS.push_back("Pisces");
}

void init_ELEMENTS() {
    ELEMENTS.push_back("Fire");
    ELEMENTS.push_back("Earth");
    ELEMENTS.push_back("Air");
    ELEMENTS.push_back("Water");
}

void init_MODES() {
    MODES.push_back("Cardinal");
    MODES.push_back("Earth");
    MODES.push_back("Air");
}

void init_TRADITIONAL_RULERSHIP() {
    insert<str, str>(TRADITIONAL_RULERSHIP, "Aries", "Mars (+)");
    insert<str, str>(TRADITIONAL_RULERSHIP, "Taurus", "Venus (-)");
    insert<str, str>(TRADITIONAL_RULERSHIP, "Gemini", "Mercury (+)");
    insert<str, str>(TRADITIONAL_RULERSHIP, "Cancer", "Moon (-)");
    insert<str, str>(TRADITIONAL_RULERSHIP, "Leo", "Sun (+)");
    insert<str, str>(TRADITIONAL_RULERSHIP, "Virgo", "Mercury (-)");
    insert<str, str>(TRADITIONAL_RULERSHIP, "Libra", "Venus (+)");
    insert<str, str>(TRADITIONAL_RULERSHIP, "Scorpio", "Mars (-)");
    insert<str, str>(TRADITIONAL_RULERSHIP, "Sagittarius", "Jupiter (+)");
    insert<str, str>(TRADITIONAL_RULERSHIP, "Capricorn", "Saturn (-)");
    insert<str, str>(TRADITIONAL_RULERSHIP, "Aquarius", "Saturn (+)");
    insert<str, str>(TRADITIONAL_RULERSHIP, "Pisces", "Jupiter (-)");
}

void init_MODERN_RULERSHIP() {
    insert<str, str>(MODERN_RULERSHIP, "Aries", "Pluto (+)");
    insert<str, str>(MODERN_RULERSHIP, "Taurus", "Venus (-)");
    insert<str, str>(MODERN_RULERSHIP, "Gemini", "Mercury (+)");
    insert<str, str>(MODERN_RULERSHIP, "Cancer", "Moon (-)");
    insert<str, str>(MODERN_RULERSHIP, "Leo", "Sun (+)");
    insert<str, str>(MODERN_RULERSHIP, "Virgo", "Mercury (-)");
    insert<str, str>(MODERN_RULERSHIP, "Libra", "Venus (+)");
    insert<str, str>(MODERN_RULERSHIP, "Scorpio", "Pluto (-)");
    insert<str, str>(MODERN_RULERSHIP, "Sagittarius", "Neptune (+)");
    insert<str, str>(MODERN_RULERSHIP, "Capricorn", "Uranus (-)");
    insert<str, str>(MODERN_RULERSHIP, "Aquarius", "Uranus (+)");
    insert<str, str>(MODERN_RULERSHIP, "Pisces", "Neptune (-)");
}

void init_HOUSES() {
    HOUSES.push_back("House-1");
    HOUSES.push_back("House-2");
    HOUSES.push_back("House-3");
    HOUSES.push_back("House-4");
    HOUSES.push_back("House-5");
    HOUSES.push_back("House-6");
    HOUSES.push_back("House-7");
    HOUSES.push_back("House-8");
    HOUSES.push_back("House-9");
    HOUSES.push_back("House-10");
    HOUSES.push_back("House-11");
    HOUSES.push_back("House-12");
}

void init_LORDS() {
    LORDS.push_back("Lord-1");
    LORDS.push_back("Lord-2");
    LORDS.push_back("Lord-3");
    LORDS.push_back("Lord-4");
    LORDS.push_back("Lord-5");
    LORDS.push_back("Lord-6");
    LORDS.push_back("Lord-7");
    LORDS.push_back("Lord-8");
    LORDS.push_back("Lord-9");
    LORDS.push_back("Lord-10");
    LORDS.push_back("Lord-11");
    LORDS.push_back("Lord-12");
}

void init_CALC_TYPES() {
    CALC_TYPES.push_back("Calculate Expected Values");
    CALC_TYPES.push_back("Calculate Chi-Square Values");
    CALC_TYPES.push_back("Calculate Effect-Size Values");
    CALC_TYPES.push_back("Calculate Cohen's D Values");
    CALC_TYPES.push_back("Calculate Binomial Probability Values");
    CALC_TYPES.push_back("Calculate Z-Score Values");
    CALC_TYPES.push_back("Calculate Significance Values");
}

void init_ZODIAC() {
    ZODIAC.push_back("Tropical");
    ZODIAC.push_back("Sidereal");
}

void init_OPTIONAL_SELECTIONS() {
    OPTIONAL_SELECTIONS.push_back("Zodiac");
    OPTIONAL_SELECTIONS.push_back("House System");
    OPTIONAL_SELECTIONS.push_back("Orb Factors");
    OPTIONAL_SELECTIONS.push_back("Midpoint Orb Factors");
    OPTIONAL_SELECTIONS.push_back("Ignored Categories");
    OPTIONAL_SELECTIONS.push_back("Ignored Attributes");
    OPTIONAL_SELECTIONS.push_back("Year Range");
    OPTIONAL_SELECTIONS.push_back("Latitude Range");
    OPTIONAL_SELECTIONS.push_back("Longitude Range");
}

void init_RANGE_VALUES() {
    RANGE_VALUES.push_back({"From", 0, 2024, 1, 0});
    RANGE_VALUES.push_back({"To", 0, 2024, 1, 0});
}

void init_DB_COLUMNS() {
    DB_COLUMNS.push_back("Name");
    DB_COLUMNS.push_back("Gender");
    DB_COLUMNS.push_back("Rodden Rating");
    DB_COLUMNS.push_back("Year");
    DB_COLUMNS.push_back("Month");
    DB_COLUMNS.push_back("Day");
    DB_COLUMNS.push_back("Hour");
    DB_COLUMNS.push_back("Julian Day");
    DB_COLUMNS.push_back("Latitude");
    DB_COLUMNS.push_back("Longitude");
    DB_COLUMNS.push_back("Place");
    DB_COLUMNS.push_back("Country");
    DB_COLUMNS.push_back("Adb Link");
    DB_COLUMNS.push_back("Categories");
}

void init_ABOUT_COLUMNS() {
    insert<str, str>(ABOUT_COLUMNS, "Version", VERSION);
    insert<str, str>(ABOUT_COLUMNS, "Date Built", "10.06.2024");
    insert<str, str>(ABOUT_COLUMNS, "Date Updated", "10.06.2024");
    insert<str, str>(
        ABOUT_COLUMNS, 
        "Thanks To", 
        "Alois Treindl, Flavia Alonzo, Sjoerd Visser"
    );
    insert<str, str>(ABOUT_COLUMNS, "Developed By", "Tanberk C. Kutlu");
    insert<str, str>(ABOUT_COLUMNS, "Contact", "mailto://tckutlu@gmail.com");
    insert<str, str>(
        ABOUT_COLUMNS, 
        "Source Code", 
        "https://github.com/dildeolupbiten/AstroDb"
    );
}

void init_PATTERNS() {
    T_SQUARE = {"Square", "Opposite", "Square"};
    GRAND_TRINE = {"Trine", "Trine", "Trine"};
    YOD = {"Quincunx", "Sextile", "Quincunx"};
    GRAND_CROSS = {"Square", "Square", "Square", "Square"};
    KITE = {"Sextile", "Trine", "Trine", "Sextile"};
    MYSTIC_RECTANGLE = {"Sextile", "Trine", "Sextile", "Trine"};
}

