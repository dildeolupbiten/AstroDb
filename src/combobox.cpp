#include "../include/combobox.hpp"
#include "../include/utils.hpp"
#include "../include/consts.hpp"

ComboBox::ComboBox(str label, list<str> values, int other, QWidget *parent)
    : QFrame(parent) {
    setLayout(new QVBoxLayout(this));
    top = new QFrame(this);
    bottom = new QFrame(this);
    title = new QLabel(top);
    combobox = new QComboBox(bottom);
    frame = new QFrame(bottom);
    widget = new QComboBox(frame);
    this -> configItems(label, values);
    this -> createOther(other);
    this -> fill();
}

str ComboBox::get(int index) {
    return (index ? widget : combobox) -> currentText().toStdString();
}

void ComboBox::fill() {
    QFrame *fill = new QFrame(bottom);
    fill -> setFixedHeight(500);
    bottom -> layout() -> addWidget(fill);
}

void ComboBox::createOther(int other) {
    if (other) {
        QLabel *text = new QLabel("Ayanamsha", frame);
        text -> setStyleSheet("font-size: 18px;");
        widget -> addItems(strVecToQStringList(AYANAMSHA -> keys));
        frame -> layout() -> addWidget(text);
        frame -> layout() -> addWidget(widget);
        frame -> layout() -> setAlignment(text, Qt::AlignCenter);
        frame -> layout() -> setAlignment(widget, Qt::AlignCenter);
        bottom -> layout() -> addWidget(frame);
        bottom -> layout() -> setAlignment(frame, Qt::AlignTop);
    }
}

void ComboBox::configItems(str label, list<str> values) {
    top -> setLayout(new QVBoxLayout(top));
    top -> setFixedHeight(50);
    bottom -> setLayout(new QVBoxLayout(bottom));
    bottom -> setFixedHeight(550);
    title -> setText(QString::fromStdString(label));
    title -> setObjectName("selectTitle");
    top -> layout() -> addWidget(title);
    top -> layout() -> setAlignment(title, Qt::AlignCenter);
    combobox -> addItems(strVecToQStringList(values));
    bottom -> layout() -> addWidget(combobox);
    bottom -> layout() -> setAlignment(combobox, Qt::AlignCenter);
    frame -> setLayout(new QVBoxLayout(frame));
    frame -> setVisible(0);
    layout() -> addWidget(top);
    layout() -> addWidget(bottom);
    connect(
        combobox,
        &QComboBox::currentTextChanged,
        [=](){
            frame -> setVisible(
                combobox -> currentText().toStdString() == "Sidereal" ? 1 : 0
            );
        }
    );
}

