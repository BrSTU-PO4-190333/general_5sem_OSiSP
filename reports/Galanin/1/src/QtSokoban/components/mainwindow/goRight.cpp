#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::goRight()
{
    if (this->xPlayer != this->length - 1)
    {
        MapChar f0 = this->map[this->xPlayer    ][this->yPlayer];
        MapChar f1 = this->map[this->xPlayer + 1][this->yPlayer];
        MapChar f2 = this->map[this->xPlayer + 2][this->yPlayer];

        // player -> floor
        // floor  -> player
        if (f0 == player && f1 == floor)
        {
            this->xPlayer += 1;

            this->map[this->xPlayer - 1][this->yPlayer] = floor;
            this->map[this->xPlayer    ][this->yPlayer] = player;

            return;
        }

        // finPlayer -> floor
        // finish    -> player
        if (f0 == finPlayer && f1 == floor)
        {
            this->xPlayer += 1;

            this->map[this->xPlayer - 1][this->yPlayer] = finish;
            this->map[this->xPlayer    ][this->yPlayer] = player;

            return;
        }

        // player -> box    -> floor
        // floor  -> player -> box
        if (f0 == player && f1 == box && f2 == floor)
        {
            this->xPlayer += 1;

            this->map[this->xPlayer - 1][this->yPlayer] = floor;
            this->map[this->xPlayer    ][this->yPlayer] = player;
            this->map[this->xPlayer + 1][this->yPlayer] = box;

            return;
        }

        // finPlayer -> box    -> floor
        // finish    -> player -> box
        if (f0 == finPlayer && f1 == box && f2 == floor)
        {
            this->xPlayer += 1;

            this->map[this->xPlayer - 1][this->yPlayer] = finish;
            this->map[this->xPlayer    ][this->yPlayer] = player;
            this->map[this->xPlayer + 1][this->yPlayer] = box;

            return;
        }

        // finPlayer -> finBox -> floor
        // finish    -> finPlayer -> box
        if (f0 == finPlayer && f1 == finBox && f2 == floor)
        {
            this->xPlayer += 1;

            this->map[this->xPlayer - 1][this->yPlayer] = finish;
            this->map[this->xPlayer    ][this->yPlayer] = finPlayer;
            this->map[this->xPlayer + 1][this->yPlayer] = box;

            return;
        }

        // player -> finBox    -> floor
        // floor  -> finPlayer -> box
        if (f0 == player && f1 == finBox && f2 == floor)
        {
            this->xPlayer += 1;

            this->map[this->xPlayer - 1][this->yPlayer] = floor;
            this->map[this->xPlayer    ][this->yPlayer] = finPlayer;
            this->map[this->xPlayer + 1][this->yPlayer] = box;

            return;
        }

        // player -> box    -> finish
        // floor  -> player -> finBox
        if (f0 == player && f1 == box && f2 == finish)
        {
            this->xPlayer += 1;

            this->map[this->xPlayer - 1][this->yPlayer] = floor;
            this->map[this->xPlayer    ][this->yPlayer] = player;
            this->map[this->xPlayer + 1][this->yPlayer] = finBox;

            return;
        }

        // finPlayer -> box    -> finish
        // finish    -> player -> finBox
        if (f0 == finPlayer && f1 == box && f2 == finish)
        {
            this->xPlayer += 1;

            this->map[this->xPlayer - 1][this->yPlayer] = finish;
            this->map[this->xPlayer    ][this->yPlayer] = player;
            this->map[this->xPlayer + 1][this->yPlayer] = finBox;

            return;
        }

        // player -> finBox    -> finish
        // floor  -> finPlayer -> finBox
        if (f0 == player && f1 == finBox && f2 == finish)
        {
            this->xPlayer += 1;

            this->map[this->xPlayer - 1][this->yPlayer] = floor;
            this->map[this->xPlayer    ][this->yPlayer] = finPlayer;
            this->map[this->xPlayer + 1][this->yPlayer] = finBox;
            return;
        }

        // finPlayer -> finBox    -> finish
        // finish    -> finPlayer -> finBox
        if (f0 == finPlayer && f1 == finBox && f2 == finish)
        {
            this->xPlayer += 1;

            this->map[this->xPlayer - 1][this->yPlayer] = finish;
            this->map[this->xPlayer    ][this->yPlayer] = finPlayer;
            this->map[this->xPlayer + 1][this->yPlayer] = finBox;
            return;
        }

        // player -> finish
        // floor  -> finPlayer
        if (f0 == player && f1 == finish)
        {
            this->xPlayer += 1;

            this->map[this->xPlayer - 1][this->yPlayer] = floor;
            this->map[this->xPlayer    ][this->yPlayer] = finPlayer;
            return;
        }

        // finPlayer -> finish
        // finish    -> finPlayer
        if (f0 == finPlayer && f1 == finish)
        {
            this->xPlayer += 1;

            this->map[this->xPlayer - 1][this->yPlayer] = finish;
            this->map[this->xPlayer    ][this->yPlayer] = finPlayer;
            return;
        }
    }
}
