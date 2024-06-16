#include "../include/utils.hpp"

void init() {
    init_ASPECTS();
    init_PLANETS();
    init_AYANAMSHA();
    init_HOUSE_SYSTEMS();
    init_SHEETS();
    init_ATTRIBUTES();
    init_RODDEN_RATINGS();
    init_RANGES();
    init_SIGNS();
    init_ELEMENTS();
    init_MODES();
    init_TRADITIONAL_RULERSHIP();
    init_MODERN_RULERSHIP();
    init_HOUSES();
    init_LORDS();
    init_CALC_TYPES();
    init_ZODIAC();
    init_OPTIONAL_SELECTIONS();
    init_RANGE_VALUES();
    init_DB_COLUMNS();
    init_ABOUT_COLUMNS();
    init_PATTERNS();
}

Results init_RESULTS() {
    Results self;
    list2d list_ps = {PLANETS -> keys, SIGNS};
    list2d list_pe = {PLANETS -> keys, ELEMENTS};
    list2d list_pm = {PLANETS -> keys, MODES};
    list2d list_ph = {PLANETS -> keys, HOUSES};
    list2d list_hs = {HOUSES, SIGNS};
    list2d list_he = {HOUSES, ELEMENTS};
    list2d list_hm = {HOUSES, MODES};
    list2d list_lh = {LORDS, HOUSES};
    list2d list_phs = {PLANETS -> keys, HOUSES, SIGNS};
    list2d list_lth = {LORDS, SIGNS, HOUSES};
    list2d list_lmh = {LORDS, SIGNS, HOUSES};
    product<dict2d>(self.planets_in_signs, list_ps);
    product<dict2d>(self.planets_in_elements, list_pe);
    product<dict2d>(self.planets_in_modes, list_pm);
    product<dict2d>(self.planets_in_houses, list_ph);
    product<dict2d>(self.houses_in_signs, list_hs);
    product<dict2d>(self.houses_in_elements, list_he);
    product<dict2d>(self.houses_in_modes, list_hm);
    product<dict2d>(self.basic_traditional_rulership, list_lh);
    product<dict2d>(self.basic_modern_rulership, list_lh);
    product<dict3d>(self.planets_in_houses_in_signs, list_phs);
    product<dict3d>(self.detailed_traditional_rulership, list_lth);
    product<dict3d>(self.detailed_modern_rulership, list_lmh);
    staircase<dict2d>(self.sum_of_aspects, 2, 0, 0);
    staircase<dict3d>(self.aspects, 3, 0, 0);
    staircase<dict3d>(self.t_square, 3, 1, 0);
    staircase<dict3d>(self.grand_trine, 3, 1, 0);
    staircase<dict3d>(self.yod, 3, 1, 0);
    staircase<dict4d>(self.grand_cross, 4, 1, 0);
    staircase<dict4d>(self.kite, 4, 1, 0);
    staircase<dict4d>(self.mystic_rectangle, 4, 1, 0);
    staircase<dict4d>(self.midpoints, 4, 1, 1);
    return self;
}

double variance(double n, double p) { 
    return n * p * (1 - p); 
}

double stdev(double n, double p) { 
    return std::sqrt(variance(n, p)); 
}

double zscore(int n, int k, double p) {
    double st = stdev(n, k / (double)n);
    return st ? (k - (n * p)) / st : 0;
}

int hasSignificance(int n, int k, double p, double alpha) {
    return std::fabs(std::erf(zscore(n, k, p) / std::sqrt(2))) > (1 - alpha);
}

double combination(int n, int k) {
    double result = 1;
    for (int i = 0; i < k; i++) {
        result *= (n - i);
        result /= (k - i);
    }
    return result;
}

double binom(int n, int k, double p) { 
    return combination(n, k) * std::pow(p, k) * std::pow(1 - p, n - k); 
}

double pmf(int n, int k, double p) {
    double probability = .0;
    for (int i = 0; i < k + 1; i++) { probability += binom(n, i, p); }
    return probability;
}

double pdf(double k, double mu, double sd) {
    double a = std::exp(-.5 * std::pow((k - mu) / sd, 2));
    double b = (sd * std::sqrt(2 * M_PI));
    return a / b;
}

double cohensDValues(double x1, double x2, double n1, double n2) {
    double var1 = variance(n1, x1 / (double)n1);
    double x = n1 * x2 / (double)n2;
    double var2 = std::pow(
        n1 / (double)n2 * std::sqrt(variance(n2, x2 / (double)n2)), 
        2
    );
    double div = std::sqrt((var1 + var2) / (double)2);
    if (div) { return (x1 - x) / div; }
    else { return 0; }
}

double binomialValues(double x1, double x2, double n1, double n2) {
    double p1 = pmf(n1, x1, x2 / n2);
    double p2 = 100. - pmf(n1, x1 - 1, x2 / n2);
    return p1 < p2 ? -p1 : p2;
}

list<double> linspace(double start, double stop, int num) {
    double step = (stop - start) / (double)(num - 1);
    list<double> values(num);
    for (int i = 0; i < num; i++) {
        values[i] = start;
        start += step;
    }
    return values;
}

list<double> getPDFValues(list<double> x, double k, double sd) {
    size_t n = x.size();
    list<double> values(n);
    for (size_t i = 0; i < n; i++) { values[i] = pdf(x[i], k, sd); }
    return values;
}

dict<str, list<double>> getPMFValues(int n, int k) {
    dict<str, list<double>> values;
    list<double> x(n + 1);
    list<double> y(n + 1);
    for (int i = 0; i < n + 1; i++) {
        x[i] = i;
        double p = k / (double)n;
        y[i] = binom(n, i, p);
    }
    values["x"] = x;
    values["y"] = y;
    return values;
}

PlotMap plotValues(int x, int n, int n_case) {
    PlotMap data;
    if (!n || x > n) { return data; }
    double p = x / (double)n;
    if (n_case && x >= 20) {
        double new_x = x * n_case / (double)n;
        double sd = std::sqrt(x * (1 - p)) * n_case / (double)n;
        list<double> x_values = linspace(new_x - 3 * sd, new_x + 3 * sd, n);
        list<double> y_values = getPDFValues(x_values, new_x, sd);
        dict<str, list<double>> values;
        values["x"] = x_values;
        values["y"] = y_values;
        data.values = values;
        data.sd = sd;
        data.mean = x_values[
            std::distance(y_values.begin(), 
            std::find(y_values.begin(), 
            y_values.end(), 
            *std::max_element(y_values.begin(), y_values.end())))
        ];
        return data;
    } else {
        dict<str, list<double>> values = getPMFValues(n, x);
        data.values = values;
        data.sd = std::sqrt(x * (1 - p));
        data.mean = x;
        return data;
    }
}

list<str> innerSplit(str string, str sep, list<str>& splitted) {
    int first = 0;
    int last = string.find(sep);
    str item = string.substr(first, last);
    splitted.push_back(item);
    if (last == -1) { return splitted; }
    return innerSplit(
        string.substr(last + sep.length(), string.length()), 
        sep, 
        splitted
    );
}

list<str> split(str string, str sep) {
    list<str> splitted;
    return innerSplit(string, sep, splitted);
}

str replace(str string, str old, str val) {
    list<str> splitted = split(string, old);
    str result;
    size_t n = splitted.size();
    for (size_t i = 0; i < n; i++) {
        result += splitted[i];
        result += i + 1 == n ? "" : val;
    }
    return result;
}

str cReplace(str string, char old, char val) {
    std::replace(string.begin(), string.end(), old, val);
    return string;
}

str lower(str s) {
    str new_s = replace(s, "I", "i");
    std::transform(
        s.begin(),
        s.end(),
        s.begin(),
        [](unsigned char c) { return std::tolower(c); }
    );
    return s;
}

str join(str string, list<str> strings) {
    size_t n = strings.size();
    str joined;
    for (size_t i = 0; i < n; i++) {
        joined += strings[i];
        joined += i + 1 != n ? string : "";
    }
    return joined;
}

str empty(int n) {
    str s = "";
    for (int i = 0; i < n; i++) { s += " "; }
    return s;
}

std::ofstream openFile(str filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file." << std::endl;
    }
    return file;
}

list<list<str>> readCSV(str filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
    }
    str line;
    list<list<str>> data;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        list<str> row;
        str value;
        while (std::getline(iss, value, ',')) {
            row.push_back(value);
        }
        data.push_back(row);
    }
    return data;
}

void writeCSV(str filename, list<list<str>> data) {
    std::ofstream file = openFile(filename);
    for (size_t row = 0; row < data.size(); row++) {
        for (size_t col = 0; col < data[row].size(); col++) {
            file << replace(data[row][col], ",", ".") << ",";
        }
        file << "\n";
    }
    file.close();
}

void writeFile(std::ofstream& file, str key, str value, int n, int colon) {
    file << key + empty(n - key.length()) + (colon ? ": " : "") + value + "\n";
}

int getYear(str string) {
    int jul = (int)string.find("Jul") != -1;
    int greg = (int)string.find("Greg") != -1;
    list<str> splitted = split(string, " ");
    size_t n = splitted.size();
    if (jul && greg) { return std::stoi(splitted[n - 2]); }
    else if (!jul && greg) { return std::stoi(splitted[2]); }
    else if (!jul && !greg) { return std::stoi(splitted[n - 1]); }
    else if (jul && !greg) { return std::stoi(splitted[2]); }
    return 0;
}

int hemisphereIndex(str string) {
    str nswe = "nswe";
    int index = 0;
    for (size_t i = 0; i < nswe.length(); i++) {
        index = string.find(nswe[i]);
        if (index > 0 && index < 10) { return index; }
    }
    return index;
}

list<int> getCoordinates(str string) {
    list<int> coordinates;
    int i = hemisphereIndex(string);
    int symbol = (string[i] == 's' || string[i] == 'w') ? -1 : 1;
    str sub = string.substr(i + 1, string.length());
    coordinates.push_back(std::stoi(string.substr(0, i)) * symbol);
    coordinates.push_back(
        std::stoi(sub.length() > 2 ? sub.substr(0, 2) : sub)
    );
    coordinates.push_back(
        std::stoi(sub.length() > 2 ? sub.substr(2, sub.length()) : sub)
    );
    return coordinates;
}

str findAspect(
    double d1, 
    double d2,
    Dict<str, dict<str, double>> *aspects,
    str orb_type
) {
    double aspect = std::fabs(d1 - d2);
    for (auto& key: aspects -> keys) {
        double degree = aspects -> data[key]["degree"];
        double orb = aspects -> data[key][orb_type];
        if (
            (degree - orb < aspect && aspect < degree + orb)
            ||
            (degree - orb < 360 - aspect && 360 - aspect < degree + orb)
        ) { return key; }
        
    }
    return "";
}

double unitDegree(double degree) { 
    return degree >= 360 ? degree - 360 : degree; 
}

double findMidpoint(double d1, double d2) {
    if (d1 > d2) {
        if (d1 - d2 >= 180) { return unitDegree((d1 + (360 + d2)) / 2); }
        else { return unitDegree((d1 + d2) / 2); }
    } else {
        if (d2 - d1 >= 180) { return unitDegree((d2 + (360 + d1)) / 2); }
        else { return unitDegree((d2 + d1) / 2); }
    }
}

str getNow() {
    std::time_t currentTime = std::time(nullptr);
    char buffer[80];
    std::strftime(
        buffer, 
        sizeof(buffer), 
        "%Y-%m-%d_%H-%M-%S", std::localtime(&currentTime)
    );
    str string(buffer);
    return string;
}

double innerListToDouble(list<int> array, list<int> units, int index) {
    if (index == (int)units.size()) { return 0; }
    return (double)array[index] / (double)units[index] + \
        (double)innerListToDouble(array, units, index + 1);
}

double listToDouble(list<int> array, list<int> units) {
    return innerListToDouble(array, units, 0);
}

Adb getAdb(str filename) {
    Adb adb;
    list<AdbEntry> database;
    list<str> categories;
    rapidxml::file<> xmlFile(filename.c_str());
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());
    rapidxml::xml_node<> *root = doc.first_node("astrodatabank_export");
    list<int> units = {1, 60, 3600};
    for (
            rapidxml::xml_node<>* child = root -> first_node(); 
            child; 
            child = child -> next_sibling()
    ) {
        str child_name = child -> name();
        if (child_name == "adb_entry") {
            rapidxml::xml_node<> *public_data = \
                child -> first_node("public_data");
            rapidxml::xml_node<> *b_data = \
                public_data -> first_node("bdata");
            rapidxml::xml_node<> *text_data = \
                child -> first_node("text_data");
            rapidxml::xml_node<> *research_data = \
                child -> first_node("research_data");
            rapidxml::xml_node<> *category_data = \
                research_data -> first_node("categories");
            AdbEntry entry;
            entry.name = public_data -> first_node("name") -> value();
            entry.gender = public_data -> first_node("gender") -> value();
            entry.rodden_rating = public_data -> \
                first_node("roddenrating") -> value();
            entry.year = std::stoi(b_data -> first_node("sbdate") -> \
                first_attribute("iyear") -> value());
            entry.month = std::stoi(b_data -> first_node("sbdate") -> \
                first_attribute("imonth") -> value());
            entry.day = std::stoi(b_data -> first_node("sbdate") -> \
                first_attribute("iday") -> value());
            entry.hour = b_data -> first_node("sbtime") -> value();
            entry.jd = cReplace(b_data -> first_node("sbtime") -> \
                first_attribute("jd_ut") -> value(), '.', ',');
            entry.lat = listToDouble(
                getCoordinates(
                    b_data -> first_node("place") -> \
                    first_attribute("slati") -> value()
                ), 
                units
            );
            entry.lon = listToDouble(
                getCoordinates(
                    b_data -> first_node("place") -> \
                    first_attribute("slong") -> value()
                ), 
                units
            );
            entry.place = b_data -> first_node("place") -> value();
            entry.country = b_data -> first_node("country") -> value();
            entry.adb_link = text_data -> first_node("adb_link") -> value();
            list<str> cats;
            for (
                rapidxml::xml_node<>* category = category_data -> first_node();
                category;
                category = category -> next_sibling()
            ) {
                std::string cat = category -> value();
                cats.push_back(cat);
                if (cat != "") { categories.push_back(cat); }
            }
            entry.categories = cats;
            database.push_back(entry);
        }
    }
    adb.database = database;
    std::sort(categories.begin(), categories.end());
    auto it = std::unique(categories.begin(), categories.end());
    list<str> unique_categories(categories.begin(), it);
    adb.categories = unique_categories;
    return adb;
}

dict<str, str> getAttrs(double degree) {
    int index = degree / 30;
    dict<str, str> self;
    self["sign"] = SIGNS[index];
    self["element"] = ELEMENTS[index % 4];
    self["mode"] = MODES[index % 3];
    return self;
}

QStringList strVecToQStringList(list<str> vec) {
    QStringList columnList;
    for (const std::string& i : vec) { 
        columnList << QString::fromStdString(i); 
    }
    return columnList;
}

list<str> fromQListToStdStrVector(QList<QListWidgetItem*> selectedItems) {
    list<str> self;
    for (const auto& item : selectedItems) { 
        self.push_back(item -> text().toStdString());
    }
    return self;
}

