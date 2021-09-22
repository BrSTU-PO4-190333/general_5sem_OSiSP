#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::Make1Level()
{
    for (int i = 0; i < this->length; i += 1)
    {
        for (int j = 0; j < this->length; j += 1)
        {
           this->map[i][j] = floor;
        }
    }

    for (int i = 0; i < this->length; i += 1)
    {
        this->map[i][0] = wall;
        this->map[i][this->length - 1] = wall;
    }

    for (int j = 0; j < this->length; j += 1)
    {
        this->map[0][j] = wall;
        this->map[this->length-1][j] = wall;
    }

    this->map[this->xPlayer][this->yPlayer] = player;

    this->map[8][9] = box;
    this->map[7][11] = box;

    this->map[6][9] = finish;
    this->map[6][10] = finish;

    this->map[5][7] = wall;
    this->map[6][7] = wall;
    this->map[7][7] = wall;
    this->map[8][7] = wall;
    this->map[9][7] = wall;

    this->map[9][7] = wall;
    this->map[9][8] = wall;
    this->map[9][9] = wall;

    this->map[9][9] = wall;
    this->map[10][9] = wall;
    this->map[11][9] = wall;

    this->map[11][9] = wall;
    this->map[11][10] = wall;
    this->map[11][11] = wall;
    this->map[11][12] = wall;
    this->map[11][13] = wall;

    this->map[11][13] = wall;
    this->map[10][13] = wall;
    this->map[9][13] = wall;
    this->map[8][13] = wall;
    this->map[7][13] = wall;
    this->map[6][13] = wall;

    this->map[6][13] = wall;
    this->map[6][12] = wall;
    this->map[6][11] = wall;

    this->map[6][11] = wall;
    this->map[5][11] = wall;

    this->map[5][11] = wall;
    this->map[5][10] = wall;
    this->map[5][9] = wall;
    this->map[5][8] = wall;
    this->map[5][7] = wall;
}
