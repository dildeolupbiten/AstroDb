#ifndef PROGRESS_HPP
#define PROGRESS_HPP

#include "optional.hpp"

class Progress : public QFrame {
public:
    Progress(QWidget *parent = nullptr);
    QPushButton *button = nullptr;
    QFrame *top = nullptr;
    QFrame *bottom = nullptr;
    QProgressBar *progress_bar = nullptr;
    Select *categories = nullptr;
    Select *rodden_ratings = nullptr;
    Select *sheets = nullptr;
    Optional *optional = nullptr;
    void configItems();
    void run();
    void finished(int value, list<AdbEntry> records);
    void progress(int value);
    str type = "select";
    list<AdbEntry> selected;
    Results results;
    int speed;
    Selections getSelections();
    Selections selections;
    Sheets getSheets();
    Sheets selected_sheets;
};

#endif // PROGRESS_HPP

