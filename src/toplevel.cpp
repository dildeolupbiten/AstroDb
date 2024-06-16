#include "../include/toplevel.hpp"
#include "../include/utils.hpp"
#include "../include/select.hpp"

Toplevel::Toplevel(
    list<AdbEntry> adb, 
    QModelIndexList& index_list, 
    QWidget *parent
) : adb(adb), index_list(index_list), QDialog(parent) {
    top.main = new QFrame(this);
    top.left.frame = new QFrame(top.main);
    top.left.label = new QLabel(top.left.frame);
    top.left.combobox = new QComboBox(top.left.frame);
    top.right.frame = new QFrame(top.main);
    top.right.label = new QLabel(top.right.frame);
    top.right.input = new QLineEdit(top.right.frame);
    table = new QTableWidget(this);
    bottom = new QFrame(this);
    text = new QLabel(bottom);
    var = new QLabel(bottom);
    configItems();
    setHeaders();
    addData();
    selectIndexList();
}

void Toplevel::selectIndexList() {
    for (const QModelIndex& index : index_list) {
        QItemSelection selection(index, index);
        table -> selectionModel() -> select(
            selection,
            QItemSelectionModel::Select | QItemSelectionModel::Rows
        );
    }
}

list<str> Toplevel::get() {
    list<str> names;
    QModelIndexList selectedIndexes = \
        table -> selectionModel() -> selectedRows();
    for (const QModelIndex& index : selectedIndexes) {
        names.push_back(adb[index.row()].name);
    }
    return names;
}

void Toplevel::configItems() {
    setStyleSheet("background-color: #212529; color: white;");
    setWindowTitle("Select Records");
    setFixedWidth(1000);
    setFixedHeight(800);
    setLayout(new QVBoxLayout(this));
    top.main -> setLayout(new QHBoxLayout(top.main));
    top.left.frame -> setLayout(new QVBoxLayout(top.left.frame));
    top.left.combobox -> addItems(strVecToQStringList(columns));
    top.left.frame -> layout() -> addWidget(top.left.label);
    top.left.frame -> layout() -> addWidget(top.left.combobox);
    top.right.frame -> setLayout(new QVBoxLayout(top.right.frame));
    top.right.input -> setStyleSheet(
        "border: 1px solid #343a40; border-radius: 2px;"
    );
    top.right.frame -> layout() -> addWidget(top.right.label);
    top.right.frame -> layout() -> addWidget(top.right.input);
    top.main -> layout() -> addWidget(top.left.frame);
    top.main -> layout() -> addWidget(top.right.frame);
    table -> setStyleSheet("QTableWidget { background-color: #343a40; }");
    bottom -> setLayout(new QHBoxLayout(bottom));
    bottom -> setFixedWidth(250);
    text -> setText("Selected");
    var -> setText("0");
    var -> setFixedWidth(60);
    var -> setStyleSheet(
        "color: white; border: 1px solid #343a40; border-radius: 2px;"
    );
    bottom -> layout() -> addWidget(text);
    bottom -> layout() -> addWidget(var);
    layout() -> addWidget(top.main);
    layout() -> addWidget(table);
    layout() -> addWidget(bottom);
    layout() -> setAlignment(bottom, Qt::AlignCenter);
    connect(
        top.right.input,
        &QLineEdit::textEdited,
        [=](){ Toplevel::filterData(); }
    );
    connect(
        table,
        &QTableWidget::itemSelectionChanged,
        [=](){ Toplevel::changeSelection(); }
    );
}

void Toplevel::addData() {
    row_count = adb.size();
    table -> setRowCount(row_count);
    str delimiter = " - ";
    for (size_t i = 0; i < row_count; i++) {
        str name = adb[i].name;
        str gender = adb[i].gender;
        str rodden_rating = adb[i].rodden_rating;
        str year = std::to_string(adb[i].year);
        str month = std::to_string(adb[i].month);
        str day = std::to_string(adb[i].day);
        str hour = adb[i].hour;
        str jd = adb[i].jd;
        str lat = std::to_string(adb[i].lat);
        str lon = std::to_string(adb[i].lon);
        str place = adb[i].place;
        str country = adb[i].country;
        str adb_link = adb[i].adb_link;
        str categories = join(", ", adb[i].categories);
        list<str> values = {
            name, gender, rodden_rating,
            year, month, day, hour, jd, lat, lon, place,
            country, adb_link, categories
        };
        raw_data.push_back(values);
        for (int j = 0; j < col_count; j++) {
            QTableWidgetItem *item = new QTableWidgetItem(
                QString::fromStdString(values[j])
            );
            item -> setBackground(QBrush(QColor("#343a40")));;
            item -> setFlags(item -> flags() & ~Qt::ItemIsEditable);
            table -> setItem(i, j, item);
        }
    }
}

void Toplevel::filterData() {
    str column = top.left.combobox -> currentText().toStdString();
    str text = top.right.input -> text().toStdString();
    int index = findIndex(columns, column);
    for (int i = 0; i < row_count; i++) {
        str s = raw_data[i][index];
        if (s.find(text) == 0) {
            table -> setRowHidden(i, 0);
        } else {
            table -> setRowHidden(i, 1);
        }
    }
}

void Toplevel::changeSelection() {
    list<AdbEntry> new_selected;
    QModelIndexList selectedIndexes = \
        table -> selectionModel() -> selectedRows();
    for (const QModelIndex& index : selectedIndexes) {
        int row = index.row();
        new_selected.push_back(adb[row]);
    }
    selected = new_selected;
    Select *parent = reinterpret_cast<Select*>(parentWidget());
    parent -> index_list = selectedIndexes;
    QString text = QString::fromStdString(std::to_string(selected.size()));
    var -> setText(QString::fromStdString(std::to_string(selected.size())));
}

void Toplevel::setHeaders() {
    col_count = columns.size();
    table -> setColumnCount(col_count);
    for (int i = 0; i < col_count; i++) {
        QTableWidgetItem *item = new QTableWidgetItem(
            QString::fromStdString(columns[i])
        );
        table -> setHorizontalHeaderItem(i, item);
        table -> setColumnWidth(i, 120);
    }
    table -> setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
}

