#include "mainwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile file(":/Assets/qss/Obit.qss");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString qss = file.readAll();
    file.close();
    a.setDesktopFileName("MineOpt");
    a.setObjectName("MineOpt");
    a.setStyleSheet(qss);
    a.setApplicationName("MineOpt");
    a.setApplicationVersion("1.0.21");
    a.setApplicationDisplayName("MineOpt");
    MainWindow w;
    w.show();
    return a.exec();
}
