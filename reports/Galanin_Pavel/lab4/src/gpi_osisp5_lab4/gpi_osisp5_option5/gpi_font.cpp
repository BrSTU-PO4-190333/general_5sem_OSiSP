#include "gpi_mainwindow.hpp"
#include "ui_gpi_mainwindow.h"

void gpi_MainWindow::gpi_on_gpi_action_font_triggered()
{
bool gpi_ok;
QFont gpi_newFont;
// = = = = = = = = = = = = = = = =

    gpi_newFont = QFontDialog::getFont(&gpi_ok, this);

    if (gpi_ok)
    {
        ui->centralwidget->setFont(gpi_newFont);
        QSettings settings(this);
        settings.setValue("gpi_VIEWF", gpi_newFont);
    }
}
