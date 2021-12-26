#include "gpi_mainwindow.hpp"

#include <QApplication>
#include "gpi_helper_class.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gpi_MainWindow w;
    w.show();

    gpi_load_dll_gpi_helper_class();

    return a.exec();
}
