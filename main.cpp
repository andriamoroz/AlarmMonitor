#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    чомусь крашиться програма при запускувікна
    w.show();
    return a.exec();
}
