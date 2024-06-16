#ifndef ABOUT_H
#define ABOUT_H

#include "libs.hpp"

class About : public QDialog {
public:
    About(QWidget *parent = nullptr);
    ~About();
    QLabel *label;
    QFrame *frame;
    void configItems();
};

#endif // ABOUT_H
