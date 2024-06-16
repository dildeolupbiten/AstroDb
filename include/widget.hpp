#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "consts.hpp"
#include "analysis.hpp"
#include "calculations.hpp"
#include "comparison.hpp"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QFrame *top;
    QFrame *bottom;
    QPushButton *btn_analysis;
    QPushButton *btn_calculations;
    QPushButton *btn_comparison;
    Analysis *frame_analysis;
    Calculations *frame_calculations;
    Comparison *frame_comparison;
    list<QFrame*> frames;
    void openFile();
    void openAbout();
    void onButtonClick(QFrame *frame, list<QFrame*> frames);
    void configItems();
    void createMenuBar();
};
#endif // WIDGET_HPP
