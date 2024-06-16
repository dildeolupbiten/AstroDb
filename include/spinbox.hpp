#ifndef SPINBOX_HPP
#define SPINBOX_HPP

#include "consts.hpp"

class SpinBox : public QFrame {
public:
    SpinBox(
        int fill,
        str label,
        list<spinBoxMap> values,
        QWidget *parent = nullptr
    );
    QFrame *top = nullptr;
    QFrame *bottom = nullptr;
    QLabel *title = nullptr;
    QFrame *frame = nullptr;
    list<DoubleSpinBox> items = {};
    void addItems(list<spinBoxMap> values);
    void fillFrame(int fill);
    void configItems();
    dict<str, double> get();
};

#endif // SPINBOX_HPP

