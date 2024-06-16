#include "../include/worker_analysis.hpp"
#include "../include/zodiac.hpp"
#include "../include/utils.hpp"
#include "../include/spreadsheet.hpp"

WorkerAnalysis::WorkerAnalysis(
    str type,
    QProgressBar* progress_bar,
    Selections& selections,
    Sheets& selected_sheets,
    list<AdbEntry> records,
    Results& results,
    QObject* parent
) : QThread(parent), 
    type(type), 
    progress_bar(progress_bar), 
    selections(selections),
    selected_sheets(selected_sheets),
    records(records), 
    results(results) 
{
    n = records.size();
    progress_bar -> setValue(0);
    progress_bar -> setMaximum(n);
}

void WorkerAnalysis::run() {
    if (type == "select") {
        select();
    }
    else {
        analyze();
    }
}

void WorkerAnalysis::analyze() {
    int index = 0;
    int ayanamsha = AYANAMSHA -> data[selections.ayanamsha]["value"];
    char hsys = HOUSE_SYSTEMS -> data[selections.house_system]["value"];
    str zodiac = selections.zodiac;
    int size = records.size();
    selections.number_of_records = size;
    list<str> links(size);
    for (AdbEntry entry : records) {
        Zodiac z(
            std::stod(entry.jd), 
            entry.lat, 
            entry.lon, 
            hsys, 
            zodiac, 
            ayanamsha
        );
        z.getPatterns(results, selected_sheets, selections);
        links[index] = entry.adb_link;
        index++;
        emit progress(index);

    }
    Spreadsheet spreadsheet(results, selections, selected_sheets, links);
    spreadsheet.save("observed_values");
    emit finished(n, records);
}

void WorkerAnalysis::select() {
    list<AdbEntry> entries;
    list<str> genders = {"M", "F", "MF", "FM", "M/F", "F/M"};
    str male = "Male";
    str female = "Female";
    str event = "Event";
    str human = "Human";
    str nh = "North Hemisphere";
    str sh = "South Hemisphere";
    str eh = "East Hemisphere";
    str wh = "West Hemisphere";
    int i = 0;
    int has_category;
    for (AdbEntry entry : records) {
        if (entry.rodden_rating != "AA") {
            continue;
        }
        has_category = 0;
        for (str category: entry.categories) {
            if (in(selections.selected_categories, category)) {
                has_category = 1;
                break;
            }
        }
        if (!has_category) {
            continue;
        }
        if (in(selections.ignored_records, entry.name)) {
            continue;
        }
        if (!in(selections.rodden_ratings, entry.rodden_rating)) {
            continue;
        }
        if (
            (entry.gender == "M") &&
            (
                in(selections.ignored_attributes, male) ||
                in(selections.ignored_attributes, human)
            )
        ) { continue; }
        if (
            (entry.gender == "F") &&
            (
                in(selections.ignored_attributes, female) || 
                in(selections.ignored_attributes, human)
            )
        ) { continue; }
        if (
            !in(genders, entry.gender) && 
            (in(selections.ignored_attributes, event))
        ) { continue; }
        if (entry.lat > 0 && in(selections.ignored_attributes, nh)) { 
            continue; 
        }
        if (entry.lon < 0 && in(selections.ignored_attributes, sh)) { 
            continue; 
        }
        if (entry.lon > 0 && in(selections.ignored_attributes, eh)) { 
            continue; 
        }
        if (entry.lon < 0 && in(selections.ignored_attributes, wh)) { 
            continue; 
        }
        if (
            (selections.year_range["from"] && selections.year_range["to"]) &&
            !(
                (selections.year_range["from"] < entry.year) && 
                (entry.year < selections.year_range["to"])
            )
        ) { continue; }
        if (
            (selections.lat_range["from"] && selections.lat_range["to"]) &&
            !(
                (selections.lat_range["from"] < entry.lat) && 
                (entry.lat < selections.lat_range["to"])
            )
            ) { continue; }
        if (
            (selections.lon_range["from"] && selections.lon_range["to"]) &&
            !(
                (selections.lon_range["from"] < entry.lon) && 
                (entry.lon < selections.lon_range["to"])
            )
            ) { continue; }
        entries.push_back(entry);
        i++;
        emit progress(i);
    }
    emit finished(n, entries);
}

