#include "gpi_mainwindow.hpp"
#include "gpi_gamewindow.hpp"

void gpi_MainWindow::gpi_on_gpi_action_about_triggered()
{
    QLibrary gpi_lib("gpi_about");

    if (gpi_lib.load() == false)
    {
        QMessageBox::critical(this, "Error with dll", "Not found gpi_helper.dll");
        qDebug() << "Not found dll gpi_helper.dll";
        return;
    }

    typedef QStringList (*prototypeHelperDll)();

    prototypeHelperDll gpi_about = (prototypeHelperDll) gpi_lib.resolve("gpi_about");

    if (gpi_about == NULL)
    {
        QMessageBox::critical(this, "Error with dll", "Not found function gpi_about()");
        qDebug() << "Not found function gpi_about()";
        return;
    }

    gpi_about();
}

void gpi_GameWindow::gpi_on_gpi_action_about_triggered()
{
    QLibrary gpi_lib("gpi_about");

    if (gpi_lib.load() == false)
    {
        QMessageBox::critical(this, "Error with dll", "Not found gpi_helper.dll");
        qDebug() << "Not found dll gpi_helper.dll";
        return;
    }

    typedef QStringList (*prototypeHelperDll)();

    prototypeHelperDll gpi_about = (prototypeHelperDll) gpi_lib.resolve("gpi_about");

    if (gpi_about == NULL)
    {
        QMessageBox::critical(this, "Error with dll", "Not found function gpi_about()");
        qDebug() << "Not found function gpi_about()";
        return;
    }

    gpi_about();
}
