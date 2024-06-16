#ifndef COMPARISON_HPP
#define COMPARISON_HPP

#include "libs.hpp"
#include "canvas.hpp"
#include "frame.hpp"

class Comparison : public Frame {
public:
    Comparison(str title, QWidget *parent = nullptr);
    QFrame *mid = nullptr;
    Canvas *canvas = nullptr;
    QFrame *mid_left = nullptr;
    QFrame *mid_right = nullptr;
    QFrame *frame_x1 = nullptr;
    QFrame *frame_n1 = nullptr;
    QFrame *frame_x2 = nullptr;
    QFrame *frame_n2 = nullptr;
    QSpinBox *x1 = nullptr;
    QSpinBox *n1 = nullptr;
    QSpinBox *x2 = nullptr;
    QSpinBox *n2 = nullptr;
    QFrame *label_frame = nullptr;
    QFrame *var_frame = nullptr;
    QLabel *var_binomial_p_lower = nullptr;
    QLabel *var_binomial_p = nullptr;
    QLabel *var_binomial_p_upper = nullptr;
    QLabel *var_cohens_d = nullptr;
    QLabel *var_z_score = nullptr;

protected:
    void reconfigItems();
};

#endif // COMPARISON_HPP
