#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::goBottom()
{
    if (this->yPlayer != this->length - 1)
    {
        MapChar f0 = this->map[this->xPlayer][this->yPlayer];
        MapChar f1 = this->map[this->xPlayer][this->yPlayer + 1];
        MapChar f2 = this->map[this->xPlayer][this->yPlayer + 2];

        // player -> floor
        // floor  -> player
        if (f0 == player && f1 == floor)
        {
            this->yPlayer += 1;

            this->map[this->xPlayer][this->yPlayer - 1] = floor;
            this->map[this->xPlayer][this->yPlayer    ] = player;

            return;
        }

        // finPlayer -> floor
        // finish    -> player
        if (f0 == finPlayer && f1 == floor)
        {
            this->yPlayer += 1;

            this->map[this->xPlayer][this->yPlayer - 1] = finish;
            this->map[this->xPlayer][this->yPlayer    ] = player;

            return;
        }

        // player -> box    -> floor
        // floor  -> player -> box
        if (f0 == player && f1 == box && f2 == floor)
        {
            this->yPlayer += 1;

            this->map[this->xPlayer][this->yPlayer - 1] = floor;
            this->map[this->xPlayer][this->yPlayer    ] = player;
            this->map[this->xPlayer][this->yPlayer + 1] = box;

            return;
        }

        // finPlayer -> box    -> floor
        // finish    -> player -> box
        if (f0 == finPlayer && f1 == box && f2 == floor)
        {
            this->yPlayer += 1;

            this->map[this->xPlayer][this->yPlayer - 1] = finish;
            this->map[this->xPlayer][this->yPlayer    ] = player;
            this->map[this->xPlayer][this->yPlayer + 1] = box;

            return;
        }

        // player -> finBox    -> floor
        // floor  -> finPlayer -> box
        if (f0 == player && f1 == finBox && f2 == floor)
        {
            this->yPlayer += 1;

            this->map[this->xPlayer][this->yPlayer - 1] = floor;
            this->map[this->xPlayer][this->yPlayer    ] = finPlayer;
            this->map[this->xPlayer][this->yPlayer + 1] = box;

            return;
        }

        // finPlayer -> finBox    -> floor
        // finish    -> finPlayer -> box
        if (f0 == finPlayer && f1 == finBox && f2 == floor)
        {
            this->yPlayer += 1;

            this->map[this->xPlayer][this->yPlayer - 1] = finish;
            this->map[this->xPlayer][this->yPlayer    ] = finPlayer;
            this->map[this->xPlayer][this->yPlayer + 1] = box;

            return;
        }

        // player -> box    -> finish
        // floor  -> player -> finBox
        if (f0 == player && f1 == box && f2 == finish)
        {
            this->yPlayer += 1;

            this->map[this->xPlayer][this->yPlayer - 1] = floor;
            this->map[this->xPlayer][this->yPlayer    ] = player;
            this->map[this->xPlayer][this->yPlayer + 1] = finBox;

            return;
        }

        // finPlayer -> box    -> finish
        // finish    -> player -> finBox
        if (f0 == finPlayer && f1 == box && f2 == finish)
        {
            this->yPlayer += 1;

            this->map[this->xPlayer][this->yPlayer - 1] = finish;
            this->map[this->xPlayer][this->yPlayer    ] = player;
            this->map[this->xPlayer][this->yPlayer + 1] = finBox;

            return;
        }

        // player -> finBox    -> finish
        // floor  -> finPlayer -> finBox
        if (f0 == player && f1 == finBox && f2 == finish)
        {
            this->yPlayer += 1;

            this->map[this->xPlayer][this->yPlayer - 1] = floor;
            this->map[this->xPlayer][this->yPlayer    ] = finPlayer;
            this->map[this->xPlayer][this->yPlayer + 1] = finBox;
            return;
        }

        // finPlayer -> finBox    -> finish
        // finish    -> finPlayer -> finBox
        if (f0 == finPlayer && f1 == finBox && f2 == finish)
        {
            this->yPlayer += 1;

            this->map[this->xPlayer][this->yPlayer - 1] = finish;
            this->map[this->xPlayer][this->yPlayer    ] = finPlayer;
            this->map[this->xPlayer][this->yPlayer + 1] = finBox;
            return;
        }

        // player -> finish
        // floor  -> finPlayer
        if (f0 == player && f1 == finish)
        {
            this->yPlayer += 1;

            this->map[this->xPlayer][this->yPlayer - 1] = floor;
            this->map[this->xPlayer][this->yPlayer    ] = finPlayer;
            return;
        }

        // finPlayer -> finish
        // finish    -> finPlayer
        if (f0 == finPlayer && f1 == finish)
        {
            this->yPlayer += 1;

            this->map[this->xPlayer][this->yPlayer - 1] = finish;
            this->map[this->xPlayer][this->yPlayer    ] = finPlayer;
            return;
        }
    }
}
