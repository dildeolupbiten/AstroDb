#include "../include/spreadsheet.hpp"
#include "../include/utils.hpp"

Spreadsheet::Spreadsheet(
    Results& results,
    Selections& selections,
    Sheets& sheets,
    list<str>& links
) : results(results), selections(selections), sheets(sheets), links(links) {};

void Spreadsheet::writeInfo(str sheetname, str datetime) {
    std::ofstream file = openFile(sheetname);
    list<str> splitted = split(datetime, "_");
    str date = splitted[0];
    str time = replace(splitted[1], "-", ":");
    str dt = date + " " + time;
    writeFile(file, (std::string)"Datetime", dt, 20, 1);
    str number_of_records = std::to_string(selections.number_of_records);
    str z = (
        selections.zodiac == "Sidereal" ?
        selections.zodiac + " (" + selections.ayanamsha + ")" :
        selections.zodiac
    );
    Dict<str, str> *info = new Dict<str, str>();
    insert<str, str>(info, "Adb Version", ADB_VERSION);
    insert<str, str>(info, "Version", VERSION);
    insert<str, str>(info, "Zodiac", z);
    insert<str, str>(info, "House System", selections.house_system);
    insert<str, str>(
        info,
        "Rodden Ratings",
        join(", ", selections.rodden_ratings)
    );
    insert<str, str>(
        info,
        "Categories",
        join(", ", selections.selected_categories)
    );
    insert<str, str>(
        info,
        "Ignored Categories",
        join(", ", selections.ignored_categories)
    );
    insert<str, str>(
        info,
        "Records",
        join(", ", selections.selected_records)
    );
    insert<str, str>(
        info,
        "Ignored Records",
        join(", ", selections.ignored_records)
    );
    for (str key: info -> keys) {
        writeFile(file, key, info -> data[key], 20, 1);
    }

    std::ofstream config = openFile(
        "observed_values_" + datetime + "/config.xml"
    );
    config << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    config << "<files>\n";
    for (size_t i = 0; i < SHEETS -> keys.size() - 1; i++) {
        str s = lower(
            replace(
                replace(replace(SHEETS -> keys[i + 1], " ", "_"), "-", "_"),
                "I",
                "i"
            )
        );
        int check = 0;
        for (size_t j = 0; j < selections.sheets.size(); j++) {
            if (SHEETS ->keys[i + 1] == selections.sheets[j]) {
                check = 1;
            }
        }
        if (check) {
            config << (
                empty(4) + "<file path=\"observed_values_" + datetime + "/" +
                s + ".csv\"" + " number_of_records=\"" +
                number_of_records + "\"" + "/>\n"
            );
        }
    }
    config << "</files>\n";
    config.close();
    for (str key: ATTRIBUTES -> keys) {
        writeFile(
            file,
            key,
            (in(selections.ignored_attributes, key) ? "False" : "True"),
            20,
            1
        );
    }
    list<dict<str, double>> ranges = {
        selections.year_range,
        selections.lat_range,
        selections.lon_range
    };
    for (int i = 0; i < RANGES -> keys.size(); i++) {
        double from = ranges[i]["From"];
        double to = ranges[i]["To"];
        str value;
        if (!i) {
            value = (
                std::to_string((int)from) +
                (str)" - " +
                std::to_string((int)to)
            );
        } else {
            value = (
                replace(std::to_string(from), ",", ".") +
                (str)" - " +
                replace(std::to_string(to), ",", ".")
            );
        }
        writeFile(file, RANGES -> keys[i], value, 20, 1);
    }
    writeFile(file, "Number Of Records", number_of_records, 20, 1);
    str s1 = "Aspect";
    str s2 = "Planet To Planet";
    str s3 = "Midpoint To Planet";
    int l1 = s1.length();
    int l2 = s2.length();
    str new_str = s1 + empty(20 - l1) + s2 + empty(20 - l2) + s3;
    writeFile(file, "Orb Factors", new_str, 20, 1);
    for (int i = 0; i < ASPECTS -> keys.size(); i++) {
        str ss1 = ASPECTS -> keys[i];
        str ss2 = replace(
            std::to_string(selections.aspects ->data[ss1]["orb1"]),
            ",",
            "."
        );
        str ss3 = replace(
            std::to_string(selections.aspects ->data[ss1]["orb2"]),
            ",",
            "."
        );
        int ll1 = ss1.length();
        int ll2 = ss2.length();
        str s = (
            empty(22) + ss1 + empty(20 - ll1) + ss2 + empty(20 - ll2) + ss3
        );
        writeFile(file, s, "", 20, 0);
    }
    file.close();
};

void Spreadsheet::write2d(
    str sheetname,
    dict2d data,
    list<list<str>> columns,
    list<str> labels
    ) {
    std::ofstream file = openFile(sheetname);
    file << join(",", labels) + "\n";
    for (str key: columns[0]) {
        for (str sub_key: columns[1]) {
            file << (
                key + "," + sub_key + "," +
                     std::to_string((int)data[key][sub_key]) + "\n"
                );
        }
    }
    file.close();
};

void Spreadsheet::write3d(
    str sheetname,
    dict3d data,
    list<list<str>> columns,
    list<str> labels,
    int expr
    ) {
    std::ofstream file = openFile(sheetname);
    file << join(",", labels) + "\n";
    for (str k1: columns[0]) {
        for (str k2: columns[1]) {
            for (str k3: columns[2]) {
                file << (
                    k1 + "," + k2 + "," + k3 + "," +
                    std::to_string((int)data[k1][k2][k3]) + "\n"
                );
            }
        }
    }
    file.close();
};

void Spreadsheet::writeSumOfAspects(str sheetname) {
    std::ofstream file = openFile(sheetname);
    file << "Planet,Planet,Total\n";
    size_t n = PLANETS -> keys.size();
    for (size_t i = 0; i < n - 1; i++) {
        for (size_t j = 0; j < n - i - 1; j++) {
            str p1 = PLANETS -> keys[i];
            str p2 = PLANETS -> keys[i + j + 1];
            file << (
                p1 + "," + p2 + "," +
                     std::to_string((int)results.sum_of_aspects[p1][p2]) + "\n"
                );
        }
    }
};

void Spreadsheet::writeAspects(str sheetname) {
    std::ofstream file = openFile(sheetname);
    file << "Planet,Aspect,Planet,Total\n";
    size_t n = PLANETS -> keys.size();
    for (size_t i = 0; i < n - 1; i++) {
        for (size_t j = 0; j < ASPECTS -> keys.size(); j++) {
            for (size_t k = 0; k < n - i - 1; k++) {
                str a = ASPECTS -> keys[j];
                str p1 = PLANETS -> keys[i];
                str p2 = PLANETS -> keys[i + k + 1];
                file << (
                    p1 + "," + a + "," + p2 + "," +
                    std::to_string((int)results.aspects[p1][a][p2]) + "\n"
                );
            }
        }
    }
}

void Spreadsheet::writeMidpoints(str sheetname) {
    std::ofstream file = openFile(sheetname);
    file << "Planet,Planet,Aspect,Planet,Total\n";
    for (size_t i = 0; i < results.midpoints.size(); i++) {
        str p1 = PLANETS -> keys[i];
        list<str> PLANETS2 = pop(PLANETS -> keys, i);
        for (size_t j = 0; j < results.midpoints[p1].size(); j++) {
            str p2 = PLANETS2[j];
            list<str> PLANETS3 = pop(PLANETS2, j);
            for (size_t k = 0; k < results.midpoints[p1][p2].size(); k++) {
                str aspect = ASPECTS -> keys[k];
                dict<str, double> sub = results.midpoints[p1][p2][aspect];
                for (size_t m = 0; m < sub.size(); m++) {
                    str p3 = PLANETS3[m];
                    file << (
                        p1 + "," + p2 + "," + aspect + "," + p3 + "," +
                        std::to_string(
                            (int)results.midpoints[p1][p2][aspect][p3]
                        ) + "\n"
                    );
                }
            }
        }
    }
    file.close();
}

void Spreadsheet::writeStaircase3d(str sheetname, dict3d& result) {
    std::ofstream file = openFile(sheetname);
    file << "Planet,Planet,Planet,Total\n";
    list<str> PLANETS2, PLANETS3;
    str p1, p2, p3;
    for (int i = 0; i < 15; i++) {
        PLANETS2 = pop(PLANETS -> keys, i);
        for (int j = 0; j < 14; j++) {
            PLANETS3 = pop(PLANETS2, j);
            for (int k = 0; k < 13; k++) {
                if (k >= j) {
                    p1 = PLANETS -> keys[i];
                    p2 = PLANETS2[j];
                    p3 = PLANETS3[k];
                    file << (
                        p1 + "," + p2 + "," + p3 + "," +
                        std::to_string(
                            (int)result[p1][p2][p3]
                        ) + "\n"
                    );
                }
            }
        }
    }
    file.close();
}

void Spreadsheet::writeStaircase4d(str sheetname, dict4d& result) {
    std::ofstream file = openFile(sheetname);
    file << "Planet,Planet,Planet,Planet,Total\n";
    list<str> PLANETS2, PLANETS3, PLANETS4;
    str p1, p2, p3, p4;
    for (int i = 0; i < 15; i++) {
        PLANETS2 = pop(PLANETS -> keys, i);
        for (int j = 0; j < 14; j++) {
            PLANETS3 = pop(PLANETS2, j);
            for (int k = 0; k < 13; k++) {
                PLANETS4 = pop(PLANETS3, k);
                for (int m = 0; m < 12; m++) {
                    if (m >= k) {
                        p1 = PLANETS -> keys[i];
                        p2 = PLANETS2[j];
                        p3 = PLANETS3[k];
                        p4 = PLANETS3[k];
                        file << (
                            p1 + "," + p2 + "," + p3 + "," +
                            std::to_string((int)result[p1][p2][p3][p4]) + "\n"
                        );
                    }
                }
            }
        }
    }
    file.close();
}

void Spreadsheet::save(str filename) {
    str now = getNow();
    str path = filename + "_" + now;
    std::filesystem::path dir(path);
    std::filesystem::create_directory(dir);
    writeInfo(path + "/info.txt", now);
    list<str> planets = slice(PLANETS -> keys, 0, PLANETS -> keys.size() - 2);
    if (sheets.planets_in_signs) {
        write2d(
            path + "/planets_in_signs.csv",
            results.planets_in_signs,
            (list<list<str>>){planets, SIGNS},
            (list<str>){"Planet", "Sign", "Total"}
            );
    }
    if (sheets.planets_in_elements) {
        write2d(
            path + "/planets_in_elements.csv",
            results.planets_in_elements,
            (list<list<str>>){planets, ELEMENTS},
            (list<str>){"Planet", "Element", "Total"}
            );
    }
    if (sheets.planets_in_modes) {
        write2d(
            path + "/planets_in_modes.csv",
            results.planets_in_modes,
            (list<list<str>>){planets, MODES},
            (list<str>){"Planet", "Mode", "Total"}
            );
    }
    if (sheets.houses_in_signs) {
        write2d(
            path + "/houses_in_signs.csv",
            results.houses_in_signs,
            (list<list<str>>){HOUSES, SIGNS},
            (list<str>){"House", "Sign", "Total"}
            );
    }
    if (sheets.houses_in_elements) {
        write2d(
            path + "/houses_in_elements.csv",
            results.houses_in_elements,
            (list<list<str>>){HOUSES, ELEMENTS},
            (list<str>){"House", "Element", "Total"}
            );
    }
    if (sheets.houses_in_modes) {
        write2d(
            path + "/houses_in_modes.csv",
            results.houses_in_modes,
            (list<list<str>>){HOUSES, MODES},
            (list<str>){"House", "Mode", "Total"}
            );
    }
    if (sheets.planets_in_houses) {
        write2d(
            path + "/planets_in_houses.csv",
            results.planets_in_houses,
            (list<list<str>>){planets, HOUSES},
            (list<str>){"Planet", "House", "Total"}
            );
    }
    if (sheets.basic_traditional_rulership) {
        write2d(
            path + "/basic_traditional_rulership.csv",
            results.basic_traditional_rulership,
            (list<list<str>>){LORDS, HOUSES},
            (list<str>){"Lord", "House", "Total"}
            );
    }
    if (sheets.basic_modern_rulership) {
        write2d(
            path + "/basic_modern_rulership.csv",
            results.basic_modern_rulership,
            (list<list<str>>){LORDS, HOUSES},
            (list<str>){"Lord", "House", "Total"}
            );
    }
    if (sheets.planets_in_houses_in_signs) {
        write3d(
            path + "/planets_in_houses_in_signs.csv",
            results.planets_in_houses_in_signs,
            (list<list<str>>){planets, HOUSES, SIGNS},
            (list<str>){"Planet", "House", "Sign", "Total"},
            0
            );
    }
    if (sheets.detailed_traditional_rulership) {
        write3d(
            path + "/detailed_traditional_rulership.csv",
            results.detailed_traditional_rulership,
            (list<list<str>>){
                LORDS,
                getValues<str, str>(*TRADITIONAL_RULERSHIP),
                HOUSES
            },
            (list<str>){"Lord", "Ruler", "House", "Total"},
            1
            );
    }
    if (sheets.detailed_modern_rulership) {
        write3d(
            path + "/detailed_modern_rulership.csv",
            results.detailed_modern_rulership,
            (list<list<str>>){
                LORDS,
                getValues<str, str>(*MODERN_RULERSHIP), HOUSES
            },
            (list<str>){"Lord", "Ruler", "House", "Total"},
            1
            );
    }

    if (sheets.sum_of_aspects) {
        writeSumOfAspects(path + "/sum_of_aspects.csv");
    }
    if (sheets.aspects) {
        writeAspects(path + "/aspects.csv");
    }
    if (sheets.t_square) {
        writeStaircase3d(path + "/t_square.csv", results.t_square);
    }
    if (sheets.grand_trine) {
        writeStaircase3d(path + "/grand_trine.csv", results.grand_trine);
    }
    if (sheets.yod) {
        writeStaircase3d(path + "/yod.csv", results.yod);
    }
    if (sheets.grand_cross) {
        writeStaircase4d(path + "/grand_cross.csv", results.grand_cross);
    }
    if (sheets.kite) {
        writeStaircase4d(path + "/kite.csv", results.kite);
    }
    if (sheets.mystic_rectangle) {
        writeStaircase4d(
            path + "/mystic_rectangle.csv", 
            results.mystic_rectangle
        );
    }
    if (sheets.midpoints) {
        writeMidpoints(path + "/midpoints.csv");
    }
    std::ofstream file = openFile(filename + "_" + now + "/links.txt");
    for (std::string link : links) {
        file << link + "\n";
    }
}

