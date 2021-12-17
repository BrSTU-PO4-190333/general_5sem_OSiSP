#include "gpi_gamewindow.hpp"
#include "ui_gpi_gamewindow.h"

void gpi_GameWindow::gpi_sayWon ()
{
    const int   gpi_w           = this->gpi_WinWidth;
    const int   gpi_l           = this->gpi_length;
    int         gpi_i;
    int         gpi_j;
    QMessageBox gpi_msgBox;
    // = = = = = = = = = = = = = = = =

    gpi_i = 0;
    while (gpi_i < gpi_l)
    {
        gpi_j = 0;
        while (gpi_j < gpi_l)
        {
            if (
                    this->gpi_map[gpi_i][gpi_j] == finish
                    || this->gpi_map[gpi_i][gpi_j] == finPlayer
            )
            {
                return;
            }
            ++gpi_j;
        }
        ++gpi_i;
    }

    this->close ();
    gpi_msgBox.setStyleSheet ("QLabel{min-width: " + QString::number (gpi_w) + "px; }");
    gpi_msgBox.setText ("You won");
    gpi_msgBox.setWindowTitle ("You won");
    gpi_msgBox.exec ();
}
