#ifndef COMBOBOX_HPP
#define COMBOBOX_HPP

#include "consts.hpp"

class ComboBox : public QFrame {
public:
    ComboBox(
        str label, 
        list<str> values, 
        int other, 
        QWidget *parent = nullptr
    );
    QFrame *top = nullptr;
    QFrame *bottom = nullptr;
    QLabel *title = nullptr;
    QComboBox *combobox = nullptr;
    QFrame *frame = nullptr;
    QComboBox *widget = nullptr;
    void configItems(str label, list<str> values);
    void fill();
    void createOther(int other);
    str get(int index);
};

#endif // COMBOBOX_HPP

