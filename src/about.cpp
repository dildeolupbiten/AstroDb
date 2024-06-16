#include "../include/about.hpp"
#include "../include/consts.hpp"


About::About(QWidget *parent) : QDialog(parent) {
    label = new QLabel("AstroDb", this);
    frame = new QFrame(this);
    this -> configItems();
}

About::~About() {}

void About::configItems() {
    setLayout(new QVBoxLayout(this));
    layout() -> addWidget(label);
    layout() -> addWidget(frame);
    layout() -> setAlignment(label, Qt::AlignCenter);
    label -> setStyleSheet("font-size: 30px;");
    frame -> setLayout(new QHBoxLayout(frame));
    QFrame *left = new QFrame(frame);
    left -> setLayout(new QVBoxLayout(left));
    QFrame *right = new QFrame(frame);
    right -> setLayout(new QVBoxLayout(right));
    frame -> layout() -> addWidget(left);
    frame -> layout() -> addWidget(right);

    for (int i = 0; i < ABOUT_COLUMNS -> keys.size(); i++) {
        QLabel *label = new QLabel(left);
        label -> setText(QString::fromStdString(ABOUT_COLUMNS -> keys[i]));
        label -> setFixedHeight(25);
        left -> layout() -> addWidget(label);

        if (
            ABOUT_COLUMNS -> keys[i] == "Contact" || 
            ABOUT_COLUMNS -> keys[i] == "Source Code"
        ) {
            QPushButton *label_var = new QPushButton(right);
            label_var -> setStyleSheet(
                "color: blue; text-align: left;" \
                "padding-left: 0px; background: #212529; border: none"
            );
            label_var -> setCursor(Qt::PointingHandCursor);
            str s = ABOUT_COLUMNS -> data[ABOUT_COLUMNS -> keys[i]];
            label_var -> setText(QString::fromStdString(s));
            label_var -> setFixedHeight(25);
            right -> layout() -> addWidget(label_var);
            str url = "xdg-open " + s;
            connect(
                label_var,
                &QPushButton::clicked,
                [url](){ return system(url.c_str()); }
            );
        } else {
            QLabel *label_var = new QLabel(right);
            label_var -> setText(
                QString::fromStdString(
                    ABOUT_COLUMNS -> data[ABOUT_COLUMNS -> keys[i]]
                )
            );
            label_var -> setFixedHeight(25);
            right -> layout() -> addWidget(label_var);
        }
    }
}

