#include "../include/calculations.hpp"
#include "../include/consts.hpp"
#include "../include/utils.hpp"
#include "../include/msgbox.hpp"
#include "../include/worker_calculations.hpp"

Calculations::Calculations(str title, QWidget *parent) : Frame(title, parent) {
    mid = new QFrame(this);
    mid_left = new QFrame(mid);
    mid_right = new QFrame(mid);
    file = new QFrame(bottom);
    bottom_left = new QFrame(file);
    bottom_right = new QFrame(file);
    combobox = new QComboBox(mid_right);
    method = new QComboBox(mid_right);
    alpha = new QDoubleSpinBox(mid_right);
    empty = new QFrame(mid_right);
    file1 = new QPushButton("Open", bottom_left);
    file2 = new QPushButton("Open", bottom_right);
    button = new QPushButton("Calculate", bottom);
    progress_bar = new QProgressBar(bottom);
    reconfigItems();
};

void Calculations::reconfigItems() {
    bottom -> layout() -> addWidget(file);
    bottom -> layout() -> addWidget(button);
    bottom -> layout() -> addWidget(progress_bar);
    QFrame *fill = new QFrame(bottom);
    fill -> setFixedHeight(500);
    bottom -> layout() -> addWidget(fill);
    layout() -> removeWidget(bottom);
    layout() -> addWidget(mid);
    layout() -> addWidget(bottom);
    bottom -> layout() -> setAlignment(button, Qt::AlignCenter);
    bottom -> layout() -> setAlignment(progress_bar, Qt::AlignCenter);
    progress_bar -> setObjectName("pbar");
    mid -> setLayout(new QHBoxLayout(mid));
    mid -> layout() -> addWidget(mid_left);
    mid -> layout() -> addWidget(mid_right);
    mid -> layout() -> setAlignment(mid_left, Qt::AlignCenter);
    mid -> layout() -> setAlignment(mid_right, Qt::AlignCenter);
    QLabel *label_combobox = new QLabel("Calculation Type", mid_left);
    QLabel *label_method = new QLabel("Method", mid_left);
    QLabel *label_alpha = new QLabel("Alpha", mid_left);
    QLabel *label_fill = new QLabel("", mid_left);
    label_combobox -> setFixedHeight(25);
    label_method -> setFixedHeight(25);
    label_alpha -> setFixedHeight(25);
    label_fill -> setFixedHeight(25);
    combobox -> setFixedHeight(25);
    method -> setFixedHeight(25);
    alpha -> setFixedHeight(25);
    empty -> setFixedHeight(25);
    empty -> setVisible(false);
    label_fill -> setVisible(false);
    label_alpha -> setVisible(false);
    alpha -> setVisible(false);
    alpha -> setMinimum(0);
    alpha -> setMaximum(1);
    alpha -> setSingleStep(.000001);
    alpha -> setDecimals(6);
    mid_left -> setLayout(new QVBoxLayout(mid_left));
    mid_left -> layout() -> addWidget(label_combobox);
    mid_left -> layout() -> addWidget(label_method);
    mid_left -> layout() -> addWidget(label_alpha);
    mid_left -> layout() -> addWidget(label_fill);
    mid_right -> setLayout(new QVBoxLayout(mid_right));
    mid_right -> layout() -> addWidget(combobox);
    mid_right -> layout() -> addWidget(method);
    mid_right -> layout() -> addWidget(alpha);
    mid_right -> layout() -> addWidget(empty);
    file -> setLayout(new QHBoxLayout(file));
    file -> layout() -> addWidget(bottom_left);
    file -> layout() -> addWidget(bottom_right);
    file -> layout() -> setAlignment(bottom_left, Qt::AlignCenter);
    file -> layout() -> setAlignment(bottom_right, Qt::AlignCenter);
    QLabel *label_file1 = new QLabel(
        "Case Group: observed_values/config.xml", 
        bottom_left
    );
    QLabel *var_file1 = new QLabel("Not loaded", bottom_left);
    bottom_left -> setLayout(new QVBoxLayout(bottom_left));
    bottom_left -> layout() -> addWidget(label_file1);
    bottom_left -> layout() -> addWidget(var_file1);
    bottom_left -> layout() -> addWidget(file1);
    bottom_left -> layout() -> setAlignment(label_file1, Qt::AlignCenter);
    bottom_left -> layout() -> setAlignment(file1, Qt::AlignCenter);
    bottom_left -> layout() -> setAlignment(var_file1, Qt::AlignCenter);
    bottom_left -> setObjectName("file");
    bottom_left -> setFixedWidth(350);
    file1 -> setFixedWidth(330);
    QLabel *label_file2 = new QLabel(
        "Test Group: observed_values/config.xml", 
        bottom_right
    );
    QLabel *var_file2 = new QLabel("Not loaded", bottom_right);
    bottom_right -> setLayout(new QVBoxLayout(bottom_right));
    bottom_right -> layout() -> addWidget(label_file2);
    bottom_right -> layout() -> addWidget(var_file2);
    bottom_right -> layout() -> addWidget(file2);
    bottom_right -> layout() -> setAlignment(label_file2, Qt::AlignCenter);
    bottom_right -> layout() -> setAlignment(file2, Qt::AlignCenter);
    bottom_right -> layout() -> setAlignment(var_file2, Qt::AlignCenter);
    bottom_right -> setObjectName("file");
    bottom_right -> setFixedWidth(350);
    file2 -> setFixedWidth(330);
    label -> setStyleSheet("font-size: 30px;");
    QStringList calc_types;
    for(const auto& calc_type : CALC_TYPES) {
        calc_types << QString::fromStdString(calc_type); 
    }
    combobox -> addItems(calc_types);
    QStringList methods;
    methods << QString::fromStdString("Subcategory");
    methods << QString::fromStdString("Independent");
    method -> addItems(methods);
    label_file1 -> setText(QString::fromStdString(
        "Case Group: observed_values/config.xml")
    );
    label_file2 -> setText(QString::fromStdString(
        "Test Group: observed_values/config.xml")
    );
    connect(
        file1, 
        &QPushButton::clicked, 
        [this, var_file1](){ this -> openFile(var_file1, 1); }
    );
    connect(
        file2, 
        &QPushButton::clicked, 
        [this, var_file2](){ this -> openFile(var_file2, 2); }
    );
    connect(button, &QPushButton::clicked, [this](){ this -> calculate(); });
    connect(
        combobox, 
        &QComboBox::currentTextChanged, 
        [
            this, label_method, label_alpha, 
            label_fill, label_file1, label_file2
        ]() { 
            this -> activate(
                label_method, label_alpha, 
                label_fill, label_file1, label_file2
            ); 
        }
    );
}

void Calculations::activate(
    QLabel *label_method, 
    QLabel *label_alpha, 
    QLabel *label_fill, 
    QLabel *label_file1, 
    QLabel *label_file2
) {
    std::string text = (combobox -> currentText()).toStdString();
    if (text == "Calculate Expected Values") {
        alpha -> setVisible(false);
        label_alpha -> setVisible(false);
        method -> setVisible(true);
        label_method -> setVisible(true);
        empty -> setVisible(false);
        label_fill -> setVisible(false);
        label_file2 -> setText(
            QString::fromStdString(
                "Test Group: observed_values/config.xml"
            )
        );
    }
    else if (text == "Calculate Significance Values") {
        alpha -> setVisible(true);
        label_alpha -> setVisible(true);
        method -> setVisible(false);
        label_method -> setVisible(false);
        empty -> setVisible(false);
        label_fill -> setVisible(false);
        label_file2 -> setText(
            QString::fromStdString(
                "Test Group: observed_values/config.xml"
            )
        );
    }
    else {
        alpha -> setVisible(false);
        label_alpha -> setVisible(false);
        method -> setVisible(false);
        label_method -> setVisible(false);
        empty -> setVisible(true);
        label_fill -> setVisible(true);
        if (
            text == "Calculate Chi-Square Values" ||
            text == "Calculate Cohen's D Values" ||
            text == "Calculate Effect-Size Values"
        ) {
            label_file2 -> setText(
                QString::fromStdString(
                    "Test Group: expected_values/config.xml"
                )
            );
        }
        else {
            label_file2 -> setText(
                QString::fromStdString(
                    "Test Group: observed_values/config.xml"
                )
            );
        }
    }
}

void Calculations::openFile(QLabel *label, int n) {
    QString filename = QFileDialog::getOpenFileName(
        nullptr,
        QObject::tr("Open AstroDb XML Config Files"),
        QDir::homePath(),
        QObject::tr("XML Files (*.xml)")
    );
    if (!filename.isEmpty()) {
        str path = filename.toStdString();
        list<str> path_strings = split(path, "/");
        str file = path_strings[path_strings.size() - 1];
        label -> setText(QString::fromStdString(file + " loaded."));
        rapidxml::file<> xmlFile(path.c_str());
        rapidxml::xml_document<> doc;
        doc.parse<0>(xmlFile.data());
        rapidxml::xml_node<> *root = doc.first_node("files");
        list<DataMap> data;
        for (
            rapidxml::xml_node<>* child = root -> first_node(); 
            child; child = child -> next_sibling()
        ) {
            str name = child -> first_attribute("path") -> value();
            int number_of_records = std::stoi(
                child -> first_attribute("number_of_records") -> value()
            );
            DataMap csv = {name, readCSV(name), number_of_records};
            data.push_back(csv);
        }
        if (n == 1) { case_group = data; } else { test_group = data; }
    }
}

void Calculations::calculate() {
    if (!case_group.size() || !test_group.size()) {
        MsgBox::information(nullptr, "Info", "No files loaded.");
        return;
    }
    if (case_group.size() != test_group.size()) {
        MsgBox::information(
            nullptr, 
            "Info", 
            "Number of files did not match."
        );
        return;
    }
    str calc_type_val = (combobox -> currentText()).toStdString();
    str method_val = (method -> currentText()).toStdString();
    double alpha_val = alpha -> value();
    for (int file = 0; file < case_group.size(); file++) {
        list<str> v1 = split(case_group[file].key, "/");
        list<str> v2 = split(test_group[file].key, "/");
        str s1 = v1[v1.size() - 1];
        str s2 = v2[v2.size() - 1];
        if (s1 != s2) {
            MsgBox::information(nullptr, "Info", "Files do not match.");
            return;
        };
        if (case_group[file].data.size() != test_group[file].data.size()) {
            MsgBox::information(
                nullptr, 
                "Info", 
                "File sizes do not match."
            );
            return;
        };
    }
    WorkerCalculations *worker = new WorkerCalculations(
        progress_bar,
        case_group,
        test_group,
        calc_type_val,
        selectCalc<double(double x1, double x2, double n1, double n2)>(
            calc_type_val,
            method_val,
            alpha_val
        )
    );
    connect(
        worker,
        &WorkerCalculations::progress,
        this,
        &Calculations::progress
    );
    connect(
        worker,
        &WorkerCalculations::finished,
        this,
        &Calculations::finished
    );
    worker -> start();
}

void Calculations::progress(int value) { progress_bar -> setValue(value); }

void Calculations::finished(int value) {
    progress_bar -> setValue(value);
}
