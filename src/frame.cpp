#include "../include/frame.hpp"

Frame::Frame(str title, QWidget *parent) : QFrame(parent) {
    top = new QFrame(this);
    bottom = new QFrame(this);
    label = new QLabel(title.c_str(), top);
    configItems();
}

void Frame::configItems() {
    setLayout(new QVBoxLayout(this));
    layout() -> addWidget(top);
    layout() -> addWidget(bottom);
    layout() -> setAlignment(top, Qt::AlignCenter);
    top -> setLayout(new QHBoxLayout(top));
    bottom -> setLayout(new QVBoxLayout(bottom));
    top -> layout() -> addWidget(label);
    top -> layout() -> setAlignment(label, Qt::AlignCenter);
    setFixedHeight(850);
    top -> setFixedHeight(50);
    bottom -> setFixedHeight(800);
    label -> setStyleSheet("font-size: 30px;");
}

