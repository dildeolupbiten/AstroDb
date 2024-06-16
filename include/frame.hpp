#ifndef FRAME_HPP
#define FRAME_HPP

#include "consts.hpp"

class Frame : public QFrame {
public:
    Frame(str title, QWidget *parent = nullptr);
    QFrame *top = nullptr;
    QFrame *bottom = nullptr;
    QLabel *label = nullptr;
    void configItems();
};

#endif // FRAME_HPP

