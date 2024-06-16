#include "../include/about.hpp"
#include "../include/analysis.hpp"
#include "../include/calculations.hpp"
#include "../include/comparison.hpp"
#include "../include/widget.hpp"
#include "../include/worker_file_loader.hpp"
#include "../include/utils.hpp"

Widget::Widget(QWidget *parent) : QWidget(parent) {
    top = new QFrame(this);
    bottom = new QFrame(this);
    btn_analysis = new QPushButton("Analysis", top);
    btn_calculations = new QPushButton("Calculations", top);
    btn_comparison = new QPushButton("Comparison", top);
    frame_analysis = new Analysis("Analysis", bottom);
    frame_calculations = new Calculations("Calculations", bottom);
    frame_comparison = new Comparison("Comparison", bottom);
    frames.push_back(frame_analysis);
    frames.push_back(frame_calculations);
    frames.push_back(frame_comparison);
    this -> configItems();
    this -> createMenuBar();
}

void Widget::createMenuBar() {
    QMenuBar *menuBar = new QMenuBar(this);
    layout() -> setMenuBar(menuBar);
    QMenu *fileMenu = menuBar -> addMenu(QObject::tr("&File"));
    QMenu *aboutMenu = menuBar -> addMenu(QObject::tr("&Help"));
    QAction *openAction = fileMenu -> addAction(QObject::tr("&Open"));
    QAction *aboutAction = aboutMenu -> addAction(QObject::tr("&About"));
    connect(openAction, &QAction::triggered, [=](){ openFile(); });
    connect(aboutAction, &QAction::triggered, [=](){ openAbout(); });
}

void Widget::configItems() {
    setLayout(new QVBoxLayout(this));
    int w = 900;
    int h = 900;
    setFixedWidth(w);
    setFixedHeight(h);
    top -> setFixedHeight(50);
    top -> setLayout(new QHBoxLayout(top));
    bottom -> setFixedHeight(h - 50);
    bottom -> setLayout(new QHBoxLayout(bottom));
    layout() -> addWidget(top);
    layout() -> addWidget(bottom);
    layout() -> setAlignment(top, Qt::AlignCenter);
    layout() -> setAlignment(bottom, Qt::AlignCenter);
    btn_analysis -> setMinimumWidth(150);
    btn_calculations -> setMinimumWidth(150);
    btn_comparison -> setMinimumWidth(150); 
    frame_analysis -> setFixedWidth(w - 100);
    frame_calculations -> setFixedWidth(w - 100);
    frame_comparison -> setFixedWidth(w - 100);
    qRegisterMetaType<QItemSelection>("QItemSelection");
    top -> layout() -> addWidget(btn_analysis);
    top -> layout() -> addWidget(btn_calculations);
    top -> layout() -> addWidget(btn_comparison);
    bottom -> layout() -> addWidget(frame_analysis);
    bottom -> layout() -> addWidget(frame_calculations);
    bottom -> layout() -> addWidget(frame_comparison);
    bottom -> layout() -> setAlignment(frame_analysis, Qt::AlignCenter);
    bottom -> layout() -> setAlignment(frame_calculations, Qt::AlignCenter);
    bottom -> layout() -> setAlignment(frame_comparison, Qt::AlignCenter);
    connect(
        btn_analysis, 
        &QPushButton::clicked, 
        [=](){ onButtonClick(frame_analysis, frames); }
    );
    connect(
        btn_calculations, 
        &QPushButton::clicked, 
        [=](){ onButtonClick(frame_calculations, frames); }
    );
    connect(
        btn_comparison, 
        &QPushButton::clicked, 
        [=](){ onButtonClick(frame_comparison, frames); }
    );
    frame_analysis -> setVisible(0);
    frame_calculations -> setVisible(0);
    frame_comparison -> setVisible(0);
}

void Widget::onButtonClick(QFrame *frame, list<QFrame*> frames) {
    for (int i = 0; i < 3; i++) {
        if (frames[i] != frame) {
            frames[i] -> setVisible(0);
        } else {
            if (frames[i] -> isVisible()) {
                frames[i] -> setVisible(0);
            } else {
                frames[i] -> setVisible(1);
            }
        }
    }
}

void Widget::openAbout() {
    About *about = new About();
    about -> exec();
}

void Widget::openFile() {
    QString filename = QFileDialog::getOpenFileName(
        nullptr,
        QObject::tr("Open Adb"),
        QDir::homePath(),
        QObject::tr("XML Files (*.xml)")
        );
    if (!filename.isEmpty()) {
        str fname = filename.toStdString();
        ADB_VERSION = fname;
        WorkerFileLoader* worker = new WorkerFileLoader(fname);
        connect(worker, &WorkerFileLoader::finished, [this](const Adb& adb) {
            frame_analysis -> categories -> adb = adb.database;
            frame_analysis -> \
                optional -> ignored_categories -> adb = adb.database;
            QStringList items = strVecToQStringList(adb.categories);
            frame_analysis -> categories -> lst -> clear();
            frame_analysis -> categories -> lst -> addItems(items);
            frame_analysis -> optional -> ignored_categories -> lst -> clear();
            frame_analysis -> \
                optional -> ignored_categories -> lst -> addItems(items);
        });
        worker -> start();
    }
}

Widget::~Widget() {}

