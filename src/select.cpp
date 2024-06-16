#include "../include/select.hpp"
#include "../include/utils.hpp"

Select::Select(int mode, const char *label, QWidget *parent)
    : mode(mode), QFrame(parent) {
    title = new QLabel(label, this);
    lst = new QListWidget(this);
    if (mode) {
        button = new QPushButton("Select Records", this);
    }
    frame = new QFrame(this);
    text = new QLabel("Selected", frame);
    var = new QLabel("0", frame);
    this -> configItems();
};

list<str> Select::get() {
    return fromQListToStdStrVector(lst -> selectedItems());
}

void Select::configItems() {
    setLayout(new QVBoxLayout(this));
    title -> setObjectName("selectTitle");
    layout() -> addWidget(title);
    layout() -> setAlignment(title, Qt::AlignCenter);
    lst -> setStyleSheet("background: #343a40; color: white;");
    lst -> setSelectionMode(QAbstractItemView::ExtendedSelection);
    frame -> setLayout(new QHBoxLayout(frame));
    frame -> layout() -> addWidget(text);
    frame -> layout() -> addWidget(var);
    var -> setFixedWidth(60);
    var -> setStyleSheet("border: 1px solid #343a40; border-radius: 2px;");
    layout() -> addWidget(lst);
    if (mode) {
        button -> setFixedWidth(150);
        layout() -> addWidget(button);
        connect(
            button,
            &QPushButton::clicked,
            [this](){ openToplevel(); }
        );
    }
    layout() -> addWidget(frame);
    layout() -> setAlignment(button, Qt::AlignCenter);
    layout() -> setAlignment(frame, Qt::AlignCenter);
    connect(
        lst,
        &QListWidget::itemSelectionChanged,
        this,
        [=](){
            var -> setText(QString::number(lst -> selectedItems().size()));
        }
    );
}

void Select::openToplevel() {
    list<AdbEntry> data = {};
    toplevel = new Toplevel(!(adb.size()) ? data : adb, index_list, this);
    toplevel -> exec();
}

