#include "../include/analysis.hpp"
#include "../include/msgbox.hpp"
#include "../include/utils.hpp"
#include "../include/progress.hpp"

Analysis::Analysis(str title, QWidget *parent) : Frame(title, parent) {
    categories = new Select(1, "Select Categories", bottom);
    rodden_ratings = new Select(0, "Select Rodden Ratings", bottom);
    sheets = new Select(0, "Select Sheets", bottom);
    optional = new Optional(bottom);
    progress = new Progress(bottom);
    frame = new QFrame(bottom);
    back = new QPushButton("<<", frame);
    var = new QLabel("1/5", frame);
    next = new QPushButton(">>", frame);
    frames = {
        {categories}, 
        {rodden_ratings}, 
        {sheets}, 
        {optional}, 
        {progress}
    };
    reconfigItems();
};

void Analysis::reconfigItems() {
    progress -> categories = categories;
    progress -> rodden_ratings = rodden_ratings;
    progress -> sheets = sheets;
    progress -> optional = optional;
    rodden_ratings -> lst -> addItems(
        strVecToQStringList(RODDEN_RATINGS -> keys)
    );
    rodden_ratings -> lst -> setCurrentRow(0);
    sheets -> lst -> addItems(
        strVecToQStringList(slice(SHEETS -> keys, 1, -1))
    );
    list<str> non_active = {
        "T-Square",
        "Grand Trine",
        "Yod",
        "Grand Cross",
        "Kite",
        "Mystic Rectangle"
    };
    for (size_t i = 0; i < SHEETS -> keys.size() - 1; i++) {
        if (in<str>(non_active, SHEETS -> keys[i + 1])) {
            sheets -> lst -> item(i) -> setSelected(false);
        } else {
            sheets -> lst -> item(i) -> setSelected(true);
        }
    }

    frame -> setLayout(new QHBoxLayout(frame));
    back -> setFixedWidth(100);
    next -> setFixedWidth(100);
    frame -> layout() -> addWidget(back);
    frame -> layout() -> addWidget(var);
    frame -> layout() -> addWidget(next);
    frame -> layout() -> setAlignment(back, Qt::AlignCenter);
    frame -> layout() -> setAlignment(var, Qt::AlignCenter);
    frame -> layout() -> setAlignment(next, Qt::AlignCenter);
    frame -> setObjectName("btn_frame");
    bottom -> layout() -> addWidget(categories);
    bottom -> layout() -> addWidget(rodden_ratings);
    bottom -> layout() -> addWidget(sheets);
    bottom -> layout() -> addWidget(optional);
    bottom -> layout() -> addWidget(progress);
    bottom -> layout() -> addWidget(frame);
    QFrame *fill = new QFrame(bottom);
    bottom -> layout() -> addWidget(fill);
    fill -> setFixedHeight(50);
    rodden_ratings -> setVisible(0);
    sheets -> setVisible(0);
    optional -> setVisible(0);
    progress -> setVisible(0);
    connect(
        back, 
        &QPushButton::clicked, 
        [this]() { moveBack(); }
    );
    connect(
        next, 
        &QPushButton::clicked, 
        [this]() { moveNext(); }
    );
}

void Analysis::moveNext() {
    size_t n = 0;
    size_t m = 0;
    if (index < 3) {
        Select *select = (Select*)(frames[index].value);
        str s = select -> var -> text().toStdString();
        n = std::stoi(s);
        if (select -> toplevel) {
            m = select -> toplevel -> get().size();
        }
    }
    else {
        n = 1;
        m = 1;
    }
    if (index + 1 < total) {
        if (!n && !m) {
            MsgBox::information(
                nullptr, 
                "Info", 
                "Select at least one item."
            );
            return;
        }
        index += 1;
        if (index == 3) {
            ((Select*)frames[index - 1].value) -> setVisible(0);
            ((Optional*)frames[index].value) -> setVisible(1);
        }
        else if (index == 4) {
            ((Optional*)frames[index - 1].value) -> setVisible(0);
            ((Progress*)frames[index].value) -> setVisible(1);
        }
        else {
            ((Select*)frames[index - 1].value) -> setVisible(0);
            ((Select*)frames[index].value) -> setVisible(1);
        }
        var -> setText(
            QString::fromStdString((std::to_string)(index + 1) + "/5")
        );
    }
}

void Analysis::moveBack() {
    int n;
    if (index < 3) {
        Select *select = (Select*)(frames[index].value);
        std::string s = select -> var -> text().toStdString();
        n = std::stoi(s);
    } else {
        n = 1;
    }
    if (index - 1 >= 0) {
        if (!n) {
            MsgBox::information(
                nullptr, 
                "Info", 
                "Select at least one item."
            );
            return;
        }
        index -= 1;
        if (index == 3) {
            ((Progress*)frames[index + 1].value) -> setVisible(0);
            ((Optional*)frames[index].value) -> setVisible(1);
        }
        else if (index == 2) {
            ((Optional*)frames[index + 1].value) -> setVisible(0);
            ((Select*)frames[index].value) -> setVisible(0);
        }
        else {
            ((Select*)frames[index + 1].value) -> setVisible(0);
            ((Select*)frames[index].value) -> setVisible(0);
        }
        ((Select*)frames[index].value) -> setVisible(1);
        var -> setText(
            QString::fromStdString((std::to_string)(index + 1) + "/5")
        );
    }
}

