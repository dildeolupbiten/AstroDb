#ifndef ANALYSIS_HPP
#define ANALYSIS_HPP

#include "libs.hpp"
#include "select.hpp"
#include "optional.hpp"
#include "progress.hpp"
#include "frame.hpp"

class Analysis : public Frame {
public:
    Analysis(str title, QWidget *parent = nullptr);
    Select *categories = nullptr;
    Select *rodden_ratings = nullptr;
    Select *sheets = nullptr;
    Optional *optional = nullptr;
    Progress *progress = nullptr;
    QFrame *frame = nullptr;
    QPushButton *back = nullptr;
    QLabel *var = nullptr;
    QPushButton *next = nullptr;
    void moveBack();
    void moveNext();
    void reconfigItems();
    int index = 0;
    int total = 5;
    list<any> frames = {};
};

#endif // ANALYSIS_HPP

