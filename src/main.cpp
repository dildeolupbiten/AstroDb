#include "../include/widget.hpp"
#include "../include/utils.hpp"

int main(int argc, char *argv[])
{
    init();
    QApplication a(argc, argv);
    QFile file(":/style.qss");
    if (!file.open(QFile::ReadOnly)) {
        qWarning("Couldn't open stylesheet file.");
        return -1;
    }
    QString baseStylesheet = QLatin1String(file.readAll());
    if (QSysInfo::productType() == "windows") {
        const char* windowsStylesheet = R"(
            QSpinBox, QDoubleSpinBox {
                background: #343a40;
                color: white;
                border: none;
            }
            QSpinBox::up-arrow, QDoubleSpinBox::up-arrow {
                width: 10px;
                height: 10px;
                color: white;
            }
            QSpinBox::down-arrow, QDoubleSpinBox::down-arrow {
                width: 10px;
                height: 10px;
                color: white;
            }
            QComboBox {
	        background: #343a40;
            }
	    QHeaderView::section {
	        background: #343a40;
		color: white;
	    }
        )";
        baseStylesheet += windowsStylesheet;
    }
    a.setStyleSheet(baseStylesheet);
    Widget w;
    w.show();
    return a.exec();
}

