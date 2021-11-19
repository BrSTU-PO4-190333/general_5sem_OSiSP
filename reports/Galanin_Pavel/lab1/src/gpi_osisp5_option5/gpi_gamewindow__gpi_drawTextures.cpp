#include "gpi_gamewindow.hpp"
#include "ui_gpi_gamewindow.h"

void gpi_GameWindow::gpi_drawTextures(QPainter *gpi_painter)
{
    int             gpi_x       = this->gpi_WinWidth / this->gpi_length;
    int             gpi_y       = this->gpi_WinHeight / this->gpi_length;
    const int       gpi_l       = this->gpi_length;
    QString         gpi_path    = ":/img/_pics/err.png";
    int             gpi_i;
    int             gpi_j;
    // = = = = = = = = = = = = = = = =

    gpi_i = 0;
    while(gpi_i < gpi_l)
    {
        gpi_j = 0;
        while(gpi_j < gpi_l)
        {
            switch(this->gpi_map[gpi_i][gpi_j])
            {
                case finish:
                    gpi_path = ":/@gpi@/_assets/gpi_GameWindow__finish.png";
                    break;
                case floor:
                    gpi_path = ":/@gpi@/_assets/gpi_GameWindow__floor.png";
                    break;
                case wall:
                    gpi_path = ":/@gpi@/_assets/gpi_GameWindow__wall.png";
                    break;
                case player:
                    gpi_path = ":/@gpi@/_assets/gpi_GameWindow__player.png";
                    break;
                case finPlayer:
                    gpi_path = ":/@gpi@/_assets/gpi_GameWindow__finPlayer.png";
                    break;
                case box:
                    gpi_path = ":/@gpi@/_assets/gpi_GameWindow__box.png";
                    break;
                case finBox:
                    gpi_path = ":/@gpi@/_assets/gpi_GameWindow__finBox.png";
                    break;
                default:
                    gpi_path = ":/@gpi@/_assets/gpi_GameWindow__err.png";
                    break;
            }

            QPixmap gpi_pixmap(gpi_path);
            gpi_painter->drawPixmap(gpi_x * gpi_i, gpi_y * gpi_j, gpi_x, gpi_y, gpi_pixmap);
            ++gpi_j;
        }
        ++gpi_i;
    }
}
