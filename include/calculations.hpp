#ifndef CALCULATIONS_HPP
#define CALCULATIONS_HPP

#include "frame.hpp"

class Calculations : public Frame {
public:
    Calculations(str title, QWidget *parent = nullptr);
    QFrame *mid = nullptr;
    QFrame *mid_left = nullptr;
    QFrame *mid_right = nullptr;
    QFrame *file = nullptr;
    QFrame *bottom_left = nullptr;
    QFrame *bottom_right = nullptr;
    QComboBox *combobox = nullptr;
    QComboBox *method = nullptr;
    QDoubleSpinBox *alpha = nullptr;
    QFrame *empty = nullptr;
    QPushButton *file1 = nullptr;
    QPushButton *file2 = nullptr;
    QPushButton *button = nullptr;
    QProgressBar *progress_bar = nullptr;
    list<DataMap> case_group;
    list<DataMap> test_group;
    void reconfigItems();
    void activate(
        QLabel *label_method,
        QLabel *label_alpha,
        QLabel *label_fill,
        QLabel *label_file1,
        QLabel *label_file2
    );
    void openFile(QLabel *label, int n);
    void calculate();
    void progress(int value);
    void finished(int value);
};

#endif // CALCULATIONS_HPP

