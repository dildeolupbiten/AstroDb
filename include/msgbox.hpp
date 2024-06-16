#ifndef MSGBOXL_HPP
#define MSGBOXL_HPP

#include "libs.hpp"

class MsgBox : public QMessageBox {
public:
    MsgBox(QWidget *parent = nullptr);
    ~MsgBox();
};

#endif // MSGBOXL_HPP
