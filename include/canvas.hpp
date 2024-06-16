#ifndef CANVAS_HPP
#define CANVAS_HPP

#include "consts.hpp"

class Canvas : public QFrame {
public:
    Canvas(QWidget *parent = nullptr);
    void plot(
        QSpinBox *x1, 
        QSpinBox *n1, 
        QSpinBox *x2,
        QSpinBox *n2,
        CanvasVars vars
    );
    PlotMap case_group;
    PlotMap test_group;
protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // CANVAS_HPP
