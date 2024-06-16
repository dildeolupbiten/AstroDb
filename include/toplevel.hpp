#ifndef TOPLEVEL_HPP
#define TOPLEVEL_HPP

#include "consts.hpp"

class Toplevel : public QDialog {
public:
    Toplevel(
        list<AdbEntry> adb, 
        QModelIndexList& index_list, 
        QWidget *parent = nullptr
    );
    list<AdbEntry> adb = {};
    QModelIndexList& index_list;
    list<list<str>> raw_data = {};
    list<AdbEntry> selected = {};
    int row_count = 0;
    int col_count = 0;
    list<str> columns = DB_COLUMNS;
    filterFrame top;
    QTableWidget *table = nullptr;
    QFrame *bottom = nullptr;
    QLabel *text = nullptr;
    QLabel *var = nullptr;
    void setHeaders();
    void addData();
    void selectIndexList();
    void filterData();
    void changeSelection();
    void configItems();
    list<str> get();
};

#endif // TOPLEVEL_HPP
