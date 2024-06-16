#include "../include/utils.hpp"
#include "../include/progress.hpp"
#include "../include/worker_analysis.hpp"
#include "../include/combobox.hpp"
#include "../include/spinbox.hpp"

Progress::Progress(QWidget *parent) : QFrame(parent) {
    top = new QFrame(this);
    bottom = new QFrame(this);
    button = new QPushButton("Analyze", this);
    progress_bar = new QProgressBar(this);
    this -> configItems();
};

void Progress::configItems() {
    setLayout(new QVBoxLayout(this));
    this -> setFixedHeight(700);
    top -> setFixedHeight(200);
    top -> setLayout(new QVBoxLayout(top));
    bottom -> setFixedHeight(200);
    bottom -> setLayout(new QVBoxLayout(bottom));
    button -> setFixedWidth(100);
    progress_bar -> setFixedWidth(200);
    progress_bar -> setObjectName("pbar");
    qRegisterMetaType<list<AdbEntry>>("list<AdbEntry>");
    qRegisterMetaType<Results>("Results");
    layout() -> addWidget(top);
    layout() -> addWidget(button);
    layout() -> addWidget(progress_bar);
    layout() -> addWidget(bottom);
    layout() -> setAlignment(button, Qt::AlignCenter);
    layout() -> setAlignment(progress_bar, Qt::AlignCenter);
    layout() -> setAlignment(top, Qt::AlignCenter);
    layout() -> setAlignment(bottom, Qt::AlignCenter);
    connect(button, &QPushButton::clicked, [this](){ this -> run(); } );
}

Selections Progress::getSelections() {
    Selections self;
    self.selected_categories = categories -> get();
    if (categories -> toplevel) {
        self.selected_records = categories -> toplevel -> get();
    }
    self.rodden_ratings = rodden_ratings -> get();
    self.sheets = sheets -> get();
    self.zodiac = ((ComboBox*)(optional -> all[0].value)) -> get(0);
    self.ayanamsha = ((ComboBox*)(optional -> all[0].value)) -> get(1);
    self.house_system = ((ComboBox*)(optional -> all[1].value)) -> get(0);
    self.aspects = ASPECTS;
    dict<str, double> orb1 = ((SpinBox*)(optional -> all[2].value)) -> get();
    dict<str, double> orb2 = ((SpinBox*)(optional -> all[3].value)) -> get();
    for (auto& key: self.aspects -> keys) {
        self.aspects -> data[key]["orb1"] = orb1[key];
        self.aspects -> data[key]["orb2"] = orb2[key];
    }
    self.ignored_categories = ((Select*)(optional -> all[4].value)) -> get();
    if (((Select*)(optional -> all[4].value)) -> toplevel) {
        self.ignored_records = (
            (Select*)(optional -> all[4].value)
        ) -> toplevel -> get();
    }
    self.ignored_attributes = ((Select*)(optional -> all[5].value)) -> get();
    self.year_range = ((SpinBox*)(optional -> all[6].value)) -> get();
    self.year_range = ((SpinBox*)(optional -> all[7].value)) -> get();
    self.year_range = ((SpinBox*)(optional -> all[8].value)) -> get();
    return self;
}

Sheets Progress::getSheets() {
    Sheets self;
    if (in<str>(selections.sheets, "Houses In Modes")) {
        self.houses_in_signs++;
    }
    if (in<str>(selections.sheets, "Houses In Modes")) {
        self.houses_in_elements++;
    }
    if (in<str>(selections.sheets, "Houses In Modes")) {
        self.houses_in_modes++;
    }
    if (in<str>(selections.sheets, "Planets In Signs")) {
        self.planets_in_signs++;
    }
    if (in<str>(selections.sheets, "Planets In Elements")) {
        self.planets_in_elements++;
    }
    if (in<str>(selections.sheets, "Planets In Modes")) {
        self.planets_in_modes++;
    }
    if (in<str>(selections.sheets, "Planets In Houses")) {
        self.planets_in_houses++;
    }
    if (in<str>(selections.sheets, "Planets In Houses In Signs")) {
        self.planets_in_houses_in_signs++;
    }
    if (in<str>(selections.sheets, "Basic Traditional Rulership")) {
        self.basic_traditional_rulership++;
    }
    if (in<str>(selections.sheets, "Basic Modern Rulership")) {
        self.basic_modern_rulership++;
    }
    if (in<str>(selections.sheets, "Detailed Traditional Rulership")) {
        self.detailed_traditional_rulership++;
    }
    if (in<str>(selections.sheets, "Detailed Modern Rulership")) {
        self.detailed_modern_rulership++;
    }
    if (in<str>(selections.sheets, "Aspects")) {
        self.aspects++;
    }
    if (in<str>(selections.sheets, "Sum Of Aspects")) {
        self.sum_of_aspects++;
    }
    if (in<str>(selections.sheets, "T-Square")) {
        self.t_square++;
    }
    if (in<str>(selections.sheets, "Grand Trine")) {
        self.grand_trine++;
    }
    if (in<str>(selections.sheets, "Yod")) {
        self.yod++;
    }
    if (in<str>(selections.sheets, "Grand Cross")) {
        self.grand_cross++;
    }
    if (in<str>(selections.sheets, "Kite")) {
        self.kite++;
    }
    if (in<str>(selections.sheets, "Mystic Rectangle")) {
        self.mystic_rectangle++;
    }
    if (in<str>(selections.sheets, "Midpoints")) {
        self.midpoints++;
    }
    return self;
}

void Progress::run() {
    button -> setEnabled(0);
    list<AdbEntry> records;
    if (type == "select") {
        records = categories -> adb;
        list<str> vs = split(ADB_VERSION, "/");
    } else {
        records = selected;
    }
    selections = getSelections();
    selected_sheets = getSheets();
    results = init_RESULTS();
    WorkerAnalysis *worker = new WorkerAnalysis(
        type,
        progress_bar,
        selections,
        selected_sheets,
        records,
        results
    );
    connect(
        worker,
        &WorkerAnalysis::progress,
        this,
        &Progress::progress
    );
    connect(
        worker,
        &WorkerAnalysis::finished,
        this,
        &Progress::finished
    );
    worker -> start();
}

void Progress::progress(int value) { progress_bar -> setValue(value); }

void Progress::finished(int value, list<AdbEntry> records) {
    if (type == "select") {
        type = "analysis";
        selected = records;
        run();
    } else {
        progress_bar -> setValue(value);
        progress_bar -> setValue(0);
        type = "select";
        button -> setEnabled(1);
    }
}

