#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::drawAxes(QPainter *painter)
{
    int x = this->WinWidth / this->length;
    int y = this->WinHeight / this->length;
    for (int i = 0; i < this->length; i += 1)
    {
        for (int j = 0; j < this->length; j += 1)
        {
            QRect rect(x*i, y*j, x, y);
            painter->drawRect(rect);
        }
    }
}
