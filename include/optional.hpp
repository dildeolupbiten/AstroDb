#ifndef OPTIONAL_HPP
#define OPTIONAL_HPP

#include "consts.hpp"
#include "select.hpp"

class Optional : public QFrame {
public:
    Optional(QWidget *parent = nullptr);
    QFrame *frame = nullptr;
    QFrame *frame_left = nullptr;
    QFrame *frame_right = nullptr;
    QLabel *title;
    list<QPushButton*> buttons = {};
    list<QFrame*> frames = {};
    void createButtons();
    void createFrames();
    void configItems();
    void createAll(list<any> all);
    list<spinBoxMap> createSpinBoxValues(str orb_type);
    Select *ignored_categories = nullptr;
    list<any> all;
};

#endif // OPTIONAL_HPP

