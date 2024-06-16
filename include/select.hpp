#ifndef SELECT_HPP
#define SELECT_HPP

#include "toplevel.hpp"

class Select : public QFrame {
public:
    Select(int mode, const char *label, QWidget *parent = nullptr);
    QLabel *title = nullptr;
    QListWidget *lst = nullptr;
    QPushButton *button = nullptr;
    QFrame *frame = nullptr;
    QLabel *text = nullptr;
    QLabel *var = nullptr;
    Toplevel *toplevel = nullptr;
    list<AdbEntry> adb;
    void openToplevel();
    void configItems();
    list<str> get();
    QModelIndexList index_list;
private:
    int mode;
};

#endif // SELECT_HPP

