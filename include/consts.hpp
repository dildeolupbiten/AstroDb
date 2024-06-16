#ifndef CONSTS_HPP
#define CONSTS_HPP

#include "libs.hpp"

using str = std::string;

template <typename T>
using list = std::vector<T>;

template <typename T1, typename T2>
using dict = std::map<T1, T2>;

using list2d = list<list<str>>;
using dict2d = dict<str, dict<str, double>>;
using dict3d = dict<str, dict2d>;
using dict4d = dict<str, dict3d>;

template <typename T1, typename T2>
struct Dict {
    list<str> keys;
    dict<T1, T2> data;
};

template <typename T1, typename T2>
void insert(Dict<T1, T2> *d, str key, T2 value) {
    d -> data[key] = value;
    d -> keys.push_back(key);
};


struct CanvasVars {
    QLabel *binomial_p_lower;
    QLabel *binomial_p;
    QLabel *binomial_p_upper;
    QLabel *cohens_d;
    QLabel *z_score;
};

struct DataMap {
    str key;
    list2d data;
    int number_of_records;
};

struct leftFrame {
    QFrame *frame;
    QLabel *label;
    QComboBox *combobox;
};

struct rightFrame {
    QFrame *frame;
    QLabel *label;
    QLineEdit *input;
};

struct filterFrame {
    QFrame *main;
    leftFrame left;
    rightFrame right;
};

struct any {
    void *value;
};

struct spinBoxMap {
    str label;
    double min;
    double max;
    double step;
    double value;
};

struct DoubleSpinBox {
    str label;
    QDoubleSpinBox *spinbox;
};

struct Results {
    dict2d planets_in_signs;
    dict2d planets_in_elements;
    dict2d planets_in_modes;
    dict2d planets_in_houses;
    dict2d houses_in_signs;
    dict2d houses_in_elements;
    dict2d houses_in_modes;
    dict2d basic_traditional_rulership;
    dict2d basic_modern_rulership;
    dict3d planets_in_houses_in_signs;
    dict3d detailed_traditional_rulership;
    dict3d detailed_modern_rulership;
    dict2d sum_of_aspects;
    dict3d aspects;
    dict3d t_square;
    dict3d grand_trine;
    dict3d yod;
    dict4d grand_cross;
    dict4d kite;
    dict4d mystic_rectangle;
    dict4d midpoints;
};

struct PlotMap {
    dict<str, list<double>> values;
    double sd;
    double mean;
};

struct AdbEntry {
    str name;
    str gender;
    str rodden_rating;
    int year;
    int month;
    int day;
    str hour;
    str jd;
    double lat;
    double lon;
    str place;
    str country;
    str adb_link;
    list<str> categories;
};

struct Planet {
    str name;
    str sign;
    double degree;
    str house;
};

struct Adb {
    list<AdbEntry> database;
    list<str> categories;
};

struct Selections {
    list<str> selected_categories;
    list<str> selected_records;
    list<str> rodden_ratings;
    list<str> sheets;
    str zodiac;
    str ayanamsha;
    str house_system;
    Dict<str, dict<str, double>> *aspects;
    dict<str, double> year_range;
    dict<str, double> lat_range;
    dict<str, double> lon_range;
    list<str> ignored_categories;
    list<str> ignored_records;
    list<str> ignored_attributes;
    int number_of_records;
};

struct Sheets {
    int houses_in_signs = 0;
    int houses_in_elements = 0;
    int houses_in_modes = 0;
    int planets_in_signs = 0;
    int planets_in_elements = 0;
    int planets_in_modes = 0;
    int planets_in_houses = 0;
    int planets_in_houses_in_signs = 0;
    int basic_traditional_rulership = 0;
    int basic_modern_rulership = 0;
    int detailed_traditional_rulership = 0;
    int detailed_modern_rulership = 0;
    int sum_of_aspects = 0;
    int aspects = 0;
    int t_square = 0;
    int grand_trine = 0;
    int yod = 0;
    int grand_cross = 0;
    int kite = 0;
    int mystic_rectangle = 0;
    int midpoints = 0;
};

extern Dict<str, dict<str, double>> *ASPECTS;
extern Dict<str, int> *PLANETS;
extern Dict<str, dict<str, int>> *AYANAMSHA;
extern Dict<str, dict<str, int>> *HOUSE_SYSTEMS;
extern Dict<str, int> *SHEETS;
extern Dict<str, int> *ATTRIBUTES;
extern Dict<str, int> *RODDEN_RATINGS;
extern Dict<str, dict<str, double>> *RANGES;
extern list<str> SIGNS;
extern list<str> ELEMENTS;
extern list<str> MODES;
extern Dict<str, str> *TRADITIONAL_RULERSHIP;
extern Dict<str, str> *MODERN_RULERSHIP;
extern list<str> HOUSES;
extern list<str> LORDS;
extern list<str> CALC_TYPES;
extern list<str> ZODIAC;
extern list<str> OPTIONAL_SELECTIONS;
extern list<spinBoxMap> RANGE_VALUES;
extern list<str> DB_COLUMNS;
extern str ADB_VERSION;
extern str VERSION;
extern Dict<str, str> *ABOUT_COLUMNS;
extern list<str> T_SQUARE;
extern list<str> GRAND_TRINE;
extern list<str> YOD;
extern list<str> GRAND_CROSS;
extern list<str> KITE;
extern list<str> MYSTIC_RECTANGLE;

void init_ASPECTS();
void init_PLANETS();
void init_AYANAMSHA();
void init_HOUSE_SYSTEMS();
void init_SHEETS();
void init_ATTRIBUTES();
void init_RODDEN_RATINGS();
void init_RANGES();
void init_SIGNS();
void init_ELEMENTS();
void init_MODES();
void init_TRADITIONAL_RULERSHIP();
void init_MODERN_RULERSHIP();
void init_HOUSES();
void init_LORDS();
void init_CALC_TYPES();
void init_ZODIAC();
void init_OPTIONAL_SELECTIONS();
void init_RANGE_VALUES();
void init_DB_COLUMNS();
void init_ABOUT_COLUMNS();
void init_PATTERNS();

#endif // CONSTS_HPP

