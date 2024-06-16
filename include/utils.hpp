#ifndef UTILS_HPP
#define UTILS_HPP

#include "consts.hpp"

template <typename T>
void __product__(T& data, list<str>& prod, const list2d& keys, int n, int i) {
    if (i == n) {
        if (n == 2) {
            reinterpret_cast<dict2d&>(data)[prod[0]][prod[1]] = 0;
        }
        else if (n == 3) {
            reinterpret_cast<dict3d&>(data)[prod[0]][prod[1]][prod[2]] = 0;
        }
        return;
    }
    for (size_t col = 0; col < keys[i].size(); col++) {
        prod[i] = keys[i][col];
        __product__<T>(data, prod, keys, n, i + 1);
    }
}

template <typename T>
void product(T& data, const list2d& keys) {
    size_t n = keys.size();
    list<str> prod(n);
    __product__<T>(data, prod, keys, n, 0);
}

template <typename T>
void staircase(T& data, int d, int special, int mp) {
    list<str> keys = special ? PLANETS -> keys : ASPECTS -> keys;
    size_t n = PLANETS -> keys.size();
    size_t o = ASPECTS -> keys.size();
    int diff = special && d == 3 ? 1 : 0;
    for (size_t i = 0; i < keys.size(); i++) {
        for (size_t j = 0; j < keys.size() - diff; j++) {
            if (mp && i > j) { continue; }
            for (size_t k = 0; k < (mp ? o : n); k++) {
                for (size_t m = 0; m < (mp ? n : n); m++) {
                    if (!mp && k > m) { continue; }
                    str p1 = keys[i];
                    str p2 = keys[j];
                    str p3 = mp ? ASPECTS -> keys[k] : PLANETS -> keys[k];
                    str p4 = PLANETS -> keys[m];
                    if (d == 2) {
                        reinterpret_cast<dict2d&>(data)[p3][p4] = 0;
                    }
                    else if (d == 3) {
                        if (special && p2 != p3 && p2 != p4) {
                            reinterpret_cast<dict3d&>(data)[p2][p3][p4] = 0;
                        }
                        if (!special) {
                            reinterpret_cast<dict3d&>(data)[p2][p3][p4] = 0;
                        }
                    }
                    else if (d == 4) {
                        if (p1 != p2 && 
                            p1 != p3 && 
                            p1 != p4 && 
                            p2 != p3 && 
                            p2 != p4 &&
                            p3 != p4
                        ) 
                        { 
                            reinterpret_cast<dict4d&>(data)\
                                [p1][p2][p3][p4] = 0; 
                        }
                    }
                }
            }
            if (d < 3) { break; }
        }
        if (d < 4) { break; }
    }
}

template <typename T>
list<T> pop(list<T> array, int index) {
    list<T> popped;
    popped.insert(popped.end(), array.begin(), array.begin() + index);
    popped.insert(popped.end(), array.begin() + index + 1, array.end());
    return popped;
}

void init();

Results init_RESULTS();

double variance(double n, double p);

double stdev(double n, double p);

double zscore(int n, int k, double p);

int hasSignificance(int n, int k, double p, double alpha);

double combination(int n, int k);

double binom(int n, int k, double p);

double pmf(int n, int k, double p);

double pdf(double k, double mu, double sd);

double cohensDValues(double x1, double x2, double n1, double n2);

double binomialValues(double x1, double x2, double n1, double n2);

list<double> linspace(double start, double stop, int num);

list<double> getPDFValues(list<double> x, double k, double sd);

dict<str, list<double>> getPMFValues(int n, int k);

PlotMap plotValues(int x, int n, int n_case);

list<str> innerSplit(str string, str sep, list<str>& splitted);

list<str> split(str string, str sep);

str replace(str string, str old, str val);

str lower(str s);

str cReplace(str string, char old, char val);

str join(str sep, list<str> strings);

str empty(int n);

std::ofstream openFile(str filename);

void writeCSV(str filename, list<list<str>> data);

void writeFile(std::ofstream& file, str key, str value, int n, int colon);

list<list<str>> readCSV(str filename);

int getYear(str string);

int hemisphereIndex(str string);

list<int> getCoordinates(str string);

str findAspect(
    double d1, 
    double d2, 
    Dict<str, dict<str, double>> *aspects, 
    str orb_type
);

double unitDegree(double degree);

double findMidpoint(double d1, double d2);

str getNow();

double innerListToDouble(list<int> array, list<int> units, int index);

double listToDouble(list<int> array, list<int> units);

Adb getAdb(str filename);

dict<str, str> getAttrs(double degree);

template <typename T>
std::function<T> selectCalc(str type, str method, double alpha) {
    if (type == "Calculate Expected Values") {
        if (method == "Subcategory") {
            return [](double x1, double x2, double n1, double n2){
                return x2 * n1 / n2;
            };
        } else {
            return [](double x1, double x2, double n1, double n2){
                return n1 * (x1 + x2) / (n1 + n2);
            };
        }
    }
    else if (type == "Calculate Effect-Size Values") {
        return [](double x1, double x2, double n1, double n2){
            return x2 ?  x1 / x2 : 0;
        };
    }
    else if (type == "Calculate Chi-Square Values") {
        return [](double x1, double x2, double n1, double n2){
            return x2 ? pow(x1 - x2, .5) / x2 : 0;
        };
    }
    else if (type == "Calculate Cohen's D Values") {
        return [](double x1, double x2, double n1, double n2){
            return cohensDValues(x1, x2, n1, n2);
        };
    }
    else if (type == "Calculate Binomial Probability Values") {
        return [](double x1, double x2, double n1, double n2){
            return binomialValues(x1, x2, n1, n2);
        };
    }
    else if (type == "Calculate Z-Score Values") {
        return [](double x1, double x2, double n1, double n2){
            return zscore(n1, x1, x2 / n2);
        };
    }
    else {
        return [alpha](double x1, double x2, double n1, double n2){
            return hasSignificance(n1, x1, x2 / n2, alpha);
        };
    }
}

QStringList strVecToQStringList(list<str> vec);

list<str> fromQListToStdStrVector(QList<QListWidgetItem*> selectedItems);

template <typename T>
int findIndex(list<T> array, T item) {
    auto it = std::find(array.begin(), array.end(), item);
    size_t index = std::distance(array.begin(), it);
    if (index <= array.size()) {
        return index;
    }
    return -1;
}

template <typename T>
list<T> slice(list<T> array, int s, int e) {
    list<T> sliced;
    size_t n = array.size();
    s = 0 <= s && s < n ? s : 0;
    e = 0 <= e && e <= n ? e : n;
    for (size_t i = s; i < e; i++) {
        sliced.push_back(array[i]);
    }
    return sliced;
}

template <typename T>
int in(list<T> array, T item) {
    for (size_t i = 0; i < array.size(); i++) {
        if (array[i] == item) {
            return 1;
        }
    }
    return 0;
}

template <typename T1, typename T2>
list<T2> getValues(Dict<T1, T2>& d) {
    list<T2> self;
    for (str key: d.keys) {
        self.push_back(d.data[key]);
    }
    return self;
}


#endif // UTILS_HPP
