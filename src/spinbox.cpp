#include "../include/spinbox.hpp"

SpinBox::SpinBox(
    int fill,
    str label,
    list<spinBoxMap> values,
    QWidget *parent
) : QFrame(parent) {
    top = new QFrame(this);
    bottom = new QFrame(this);
    title = new QLabel(QString::fromStdString(label), top);
    frame = new QFrame(bottom);
    this -> configItems();
    this -> addItems(values);
    this -> fillFrame(fill);
}

void SpinBox::configItems() {
    setLayout(new QVBoxLayout(this));
    top -> setLayout(new QVBoxLayout(top));
    bottom -> setLayout(new QVBoxLayout(bottom));
    title -> setObjectName("selectTitle");
    frame -> setLayout(new QVBoxLayout(frame));
    top -> layout() -> addWidget(title);
    top -> layout() -> setAlignment(title, Qt::AlignCenter);
    bottom -> layout() -> addWidget(frame);
    bottom -> layout() -> setAlignment(frame, Qt::AlignCenter);
    layout() -> addWidget(top);
    layout() -> addWidget(bottom);
}

void SpinBox::fillFrame(int fill) {
    if (fill) {
        top -> setFixedHeight(50);
        bottom -> setFixedHeight(600);
        QFrame *fill_frame = new QFrame(bottom);
        fill_frame -> setFixedHeight(600);
        bottom -> layout() -> addWidget(fill_frame);
        bottom -> layout() -> setAlignment(fill_frame, Qt::AlignCenter);
    }
}

void SpinBox::addItems(list<spinBoxMap> values) {
    for (const spinBoxMap& spinbox : values)  {
        QFrame *sub = new QFrame(frame);
        sub -> setLayout(new QHBoxLayout(sub));
        QLabel *label = new QLabel(frame);
        label -> setText(QString::fromStdString(spinbox.label));
        label -> setFixedWidth(150);
        QDoubleSpinBox *sb = new QDoubleSpinBox(frame);
        sb -> setFixedWidth(100);
        sb -> setMinimum(spinbox.min);
        sb -> setMaximum(spinbox.max);
        sb -> setSingleStep(spinbox.step);
        sb -> setValue(spinbox.value);
        sub -> layout() -> addWidget(label);
        sub -> layout() -> addWidget(sb);
        frame -> layout() -> addWidget(sub);
        frame -> layout() -> setAlignment(sub, Qt::AlignCenter);
        items.push_back({spinbox.label, sb});
    }
}
dict<str, double> SpinBox::get() {
    dict<str, double> self;
    for (const auto& item : items) {
        self[item.label] = (double)(item.spinbox -> value());
    }
    return self;
}

