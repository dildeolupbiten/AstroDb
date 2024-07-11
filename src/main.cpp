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
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    QString baseStylesheet = QLatin1String(file.readAll());
    a.setStyleSheet(baseStylesheet);
    Widget w;
    w.show();
    return a.exec();
}

