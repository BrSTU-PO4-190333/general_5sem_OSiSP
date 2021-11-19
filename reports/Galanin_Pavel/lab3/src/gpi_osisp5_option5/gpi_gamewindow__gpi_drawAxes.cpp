#include "gpi_gamewindow.hpp"
#include "ui_gpi_gamewindow.h"

void gpi_GameWindow::gpi_drawAxes(QPainter *gpi_painter)
{
    int         gpi_x   = this->gpi_WinWidth / this->gpi_length;
    int         gpi_y   = this->gpi_WinHeight / this->gpi_length;
    const int   gpi_l   = this->gpi_length;
    int         gpi_i;
    int         gpi_j;
    // = = = = = = = = = = = = = = = =

    gpi_i = 0;
    while(gpi_i < gpi_l)
    {
        gpi_j = 0;
        while(gpi_j < gpi_l)
        {
            QRect gpi_rect(gpi_x * gpi_i, gpi_y * gpi_j, gpi_x, gpi_y);
            gpi_painter->drawRect(gpi_rect);
            ++gpi_j;
        }
        ++gpi_i;
    }
}
