#include "../include/optional.hpp"
#include "../include/combobox.hpp"
#include "../include/spinbox.hpp"
#include "../include/select.hpp"
#include "../include/utils.hpp"

Optional::Optional(QWidget *parent) : QFrame(parent) {
    title = new QLabel("Optional Selections", this);
    frame = new QFrame(this);
    frame_left = new QFrame(this);
    frame_right = new QFrame(this);
    this -> configItems();
    this -> createButtons();
    this -> createFrames();
    this -> createAll(all);
}

void Optional::configItems() {
    setLayout(new QVBoxLayout(this));
    setFixedHeight(700);
    title -> setObjectName("selectTitle");
    frame -> setLayout(new QHBoxLayout(frame));
    frame -> setFixedHeight(650);
    frame_left -> setLayout(new QVBoxLayout(frame_left));
    frame_left -> setFixedWidth(200);
    frame_right -> setLayout(new QVBoxLayout(frame_right));
    frame_right -> setFixedWidth(700);
    frame -> layout() -> addWidget(frame_left);
    frame -> layout() -> addWidget(frame_right);
    frame -> layout() -> setAlignment(frame_right, Qt::AlignCenter);
    layout() -> addWidget(title);
    layout() -> addWidget(frame);
    layout() -> setAlignment(title, Qt::AlignCenter);
    layout() -> setAlignment(frame, Qt::AlignCenter);
}

void Optional::createFrames() {
    ComboBox *zodiac = new ComboBox("Zodiac", ZODIAC, 1, frame_right);
    ComboBox *house_systems = new ComboBox(
        "House Systems",
        HOUSE_SYSTEMS -> keys, 0, frame_right
    );
    SpinBox *orb_factors = new SpinBox(
        0,
        "Orb Factors",
        createSpinBoxValues("orb1"),
        frame_right
    );
    SpinBox *midpoint_orb_factors = new SpinBox(
        0,
        "Midpoint Orb Factors",
        createSpinBoxValues("orb2"),
        frame_right
    );
    ignored_categories = new Select(1, "Ignored Categories", frame_right);
    ignored_categories -> setFixedHeight(600);
    Select *ignored_attributes = new Select(
        0,
        "Ignored Attributes",
        frame_right
    );
    ignored_attributes -> setFixedHeight(600);
    ignored_attributes -> lst -> addItems(
        strVecToQStringList(ATTRIBUTES -> keys)
    );
    ignored_attributes -> lst -> setCurrentRow(0);
    SpinBox *year_range = new SpinBox(
        1,
        "Year Range",
        RANGE_VALUES,
        frame_right
    );
    SpinBox *lat_range = new SpinBox(
        1,
        "Latitude Range",
        RANGE_VALUES,
        frame_right
    );
    SpinBox *lon_range = new SpinBox(
        1,
        "Longitude Range",
        RANGE_VALUES,
        frame_right
    );
    all = {
        {zodiac}, {house_systems},
        {orb_factors}, {midpoint_orb_factors},
        {ignored_categories}, {ignored_attributes},
        {year_range}, {lat_range}, {lon_range}
    };
}

void Optional::createButtons() {
    for (const auto& selection : OPTIONAL_SELECTIONS) {
        QPushButton *btn = new QPushButton(
            QString::fromStdString(selection), frame_left
        );
        frame_left -> layout() -> addWidget(btn);
        buttons.push_back(btn);
    }
}

list<spinBoxMap> Optional::createSpinBoxValues(str orb_type) {
    list<spinBoxMap> spinBoxValues;
    for (auto& key: ASPECTS -> keys) {
        spinBoxMap item;
        item.label = key;
        item.min = 0;
        item.max = 10;
        item.step = .1;
        item.value = ASPECTS -> data[key][orb_type];
        spinBoxValues.push_back(item);
    }
    return spinBoxValues;
}

void Optional::createAll(list<any> all) {
    size_t n = all.size();
    for (size_t i = 0; i < n; i++) {
        QFrame *x = (QFrame*)all[i].value;
        frame_right -> layout() -> addWidget(x);
        frame_right -> layout() -> setAlignment(x, Qt::AlignCenter);
        x -> setVisible(0);
        connect(buttons[i], &QPushButton::clicked, [x, i, n, all](){
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    ((QFrame*)all[j].value) -> setVisible(0);
                } else {
                    x -> setVisible(x -> isVisible() ? 0 : 1);
                }
            }
        });
    }
}

