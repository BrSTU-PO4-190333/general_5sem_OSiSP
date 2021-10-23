#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::drawTextures(QPainter *painter)
{
    int x = this->WinWidth / this->length;
    int y = this->WinHeight / this->length;
    for (int i = 0; i < this->length; i += 1)
    {
        for (int j = 0; j < this->length; j += 1)
        {
            QString path = ":/img/_pics/err.png";
            if (this->map[i][j] == finish)
            {
                path = ":/img/_pics/finish.png";
            }
            else if (this->map[i][j] == floor)
            {
                path = ":/img/_pics/floor.png";
            }
            else if (this->map[i][j] == wall)
            {
                path = ":/img/_pics/wall.png";
            }
            else if (this->map[i][j] == player)
            {
                path = ":/img/_pics/player.png";
            }
            else if (this->map[i][j] == finPlayer)
            {
                path = ":/img/_pics/finPlayer.png";
            }
            else if (this->map[i][j] == box)
            {
                path = ":/img/_pics/box.png";
            }
            else if (this->map[i][j] == finBox)
            {
                path = ":/img/_pics/finBox.png";
            }

            QPixmap pixmap(path);
            painter->drawPixmap(x*i, y*j, x, y, pixmap);
        }
    }
}
