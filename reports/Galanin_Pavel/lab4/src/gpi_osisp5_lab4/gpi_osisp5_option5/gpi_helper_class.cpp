#include "gpi_helper_class.hpp"

void gpi_load_dll_gpi_helper_class()
{
    QLibrary gpi_lib("gpi_helper_class");

    if (gpi_lib.load() == false)
    {
        QMessageBox gpi_mb;
        gpi_mb.setWindowTitle("Error with dll");
        gpi_mb.setText("Not found gpi_helper_class.dll");
        gpi_mb.exec();
        qDebug() << "Not found dll gpi_helper_class.dll";
        return;
    }

    typedef gpi_helper_class* (*prototypeHelperClass)();
    prototypeHelperClass gpi_helper_class = (prototypeHelperClass) gpi_lib.resolve("gpi_create_gpi_helper_class");

    if (gpi_helper_class == NULL)
    {
        QMessageBox gpi_mb;
        gpi_mb.setWindowTitle("Error with dll");
        gpi_mb.setText("Not found function gpi_helper_class()");
        gpi_mb.exec();
        qDebug() << "Not found function gpi_helper_class()";
        return;
    }

    qDebug() << " Loaded gpi_helper_class()";
}
