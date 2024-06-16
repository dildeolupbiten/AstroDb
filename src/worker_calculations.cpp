#include "../include/worker_calculations.hpp"
#include "../include/utils.hpp"

WorkerCalculations::WorkerCalculations(
    QProgressBar* progress_bar,
    list<DataMap>& data1,
    list<DataMap>& data2,
    str calc_type_val,
    std::function<double(double x1, double x2, double n1, double n2)> func,
    QObject* parent
) : QThread(parent),
    progress_bar(progress_bar),
    data1(data1), data2(data2),
    calc_type_val(calc_type_val),
    func(func)
{
        progress_bar -> setValue(0);
        progress_bar -> setMaximum(data1.size());
}

str WorkerCalculations::getFilename() {
    if (calc_type_val == "Calculate Expected Values") {
        return "expected_values";
    }
    if (calc_type_val == "Calculate Chi-Square Values") {
        return "chi_square_values";
    }
    if (calc_type_val == "Calculate Effect-Size Values") {
        return "effect_size_values";
    }
    if (calc_type_val == "Calculate Cohen's D Values") {
        return "cohens_d_values";
    }
    if (calc_type_val == "Calculate Binomial Probability Values") {
        return "binomial_probability";
    }
    if (calc_type_val == "Calculate Significance Values") {
        return "significance_values";
    }
    return "z_score_values";
}

void WorkerCalculations::run() {
    str path = getFilename();
    str now = getNow();
    std::filesystem::path dir(path + "_" + now);
    std::filesystem::create_directory(dir);
    list<str> files;
    for (size_t file = 0; file < data1.size(); file++) {
        files.push_back(data1[file].key);
        size_t r = data1[file].data.size();
        for (size_t row = 0; row < r; row++) {
            size_t c = data1[file].data[row].size();
            list<double> temp_row(c);
            for (size_t col = 0; col < c; col++) {
                if (row && col == c - 1){
                     double result = func(
                        std::stod(data1[file].data[row][col]),
                        std::stod(data2[file].data[row][col]),
                        (double)data1[file].number_of_records,
                        (double)data2[file].number_of_records
                    );
                    data1[file].data[row][col] = std::to_string(result);
                }
            }
        }
        list<str> v = split(data1[file].key, "/");
        str s = v[v.size() - 1];
        writeCSV(path + "_" + now + "/" + s, data1[file].data);
        emit progress(file + 1);
    }
    std::ofstream config = openFile(path + "_" + now + "/config.xml");
    config << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    config << "<files>\n";
    for (size_t i = 0; i < data1.size(); i++) {
        list<str> v = split(files[i], "/");
        str s = v[v.size() - 1];
        config << empty(4) + "<file path=\"" + path + "_" + now + "/" + s \
            + "\" number_of_records=\"" \
            + std::to_string(data1[i].number_of_records) + "\"" + "/>\n";
    }
    config << "</files>\n";
    config.close();
    emit finished(data1.size());
}

