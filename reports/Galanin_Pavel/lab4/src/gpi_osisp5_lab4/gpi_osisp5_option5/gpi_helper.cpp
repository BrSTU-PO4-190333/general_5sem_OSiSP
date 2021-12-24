#include "gpi_gamewindow.hpp"

// gpi_ Функция, которая рестратит уровень
void gpi_GameWindow::gpi_on_gpi_action_restart_triggered()
{
    QLibrary gpi_lib("gpi_helper");

    if (gpi_lib.load() == false)
    {
        QMessageBox::critical(this, "Error with dll", "Not found gpi_helper.dll");
        qDebug() << "Not found dll gpi_helper.dll";
        return;
    }

    typedef QStringList (*prototypeHelperDll)();

    if (this->gpi_lvl == 1)
    {
        prototypeHelperDll gpi_get_1_level = (prototypeHelperDll) gpi_lib.resolve("gpi_get_1_level");

        if (gpi_get_1_level == NULL)
        {
            QMessageBox::critical(this, "Error with dll", "Not found function gpi_get_1_level()");
            qDebug() << "Not found function gpi_get_1_level()";
            return;
        }

        gpi_generate(gpi_get_1_level());
        gpi_on_gpi_action_align_triggered();
        return;
    }

    if (this->gpi_lvl == 2)
    {
        prototypeHelperDll gpi_get_2_level = (prototypeHelperDll) gpi_lib.resolve("gpi_get_2_level");

        if (gpi_get_2_level == NULL)
        {
            QMessageBox::critical(this, "Error with dll", "Not found function gpi_get_2_level()");
            qDebug() << "Not found function gpi_get_2_level()";
            return;
        }

        gpi_generate(gpi_get_2_level());
        gpi_on_gpi_action_align_triggered();
        return;
    }

    if (this->gpi_lvl == 3)
    {
        prototypeHelperDll gpi_get_3_level = (prototypeHelperDll) gpi_lib.resolve("gpi_get_3_level");

        if (gpi_get_3_level == NULL)
        {
            QMessageBox::critical(this, "Error with dll", "Not found function gpi_get_3_level()");
            qDebug() << "Not found function gpi_get_3_level()";
            return;
        }

        gpi_generate(gpi_get_3_level());
        gpi_on_gpi_action_align_triggered();
        return;
    }

    if (this->gpi_lvl == 4)
    {
        prototypeHelperDll gpi_get_4_level = (prototypeHelperDll) gpi_lib.resolve("gpi_get_4_level");

        if (gpi_get_4_level == NULL)
        {
            QMessageBox::critical(this, "Error with dll", "Not found function gpi_get_4_level()");
            qDebug() << "Not found function gpi_get_4_level()";
            return;
        }

        gpi_generate(gpi_get_4_level());
        gpi_on_gpi_action_align_triggered();
        return;
    }

    prototypeHelperDll gpi_get_1_level = (prototypeHelperDll) gpi_lib.resolve("gpi_get_1_level");

    if (gpi_get_1_level == NULL)
    {
        QMessageBox::critical(this, "Error with dll", "Not found function gpi_get_1_level");
        qDebug() << "Not found function gpi_get_1_level()";
        return;
    }

    gpi_generate(gpi_get_1_level());
    gpi_on_gpi_action_align_triggered();
}
