#include "gpi_mainwindow.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gpi_MainWindow w;
    w.show();
    return a.exec();
}
