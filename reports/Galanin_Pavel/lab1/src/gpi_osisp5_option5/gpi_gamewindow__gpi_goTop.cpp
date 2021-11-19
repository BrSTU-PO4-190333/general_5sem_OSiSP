#include "gpi_gamewindow.hpp"
#include "ui_gpi_gamewindow.h"

void gpi_GameWindow::gpi_goTop ()
{
    int         gpi_px          = this->gpi_xPlayer;
    int         gpi_py          = this->gpi_yPlayer;
    gpi_MapChar gpi_c0;
    gpi_MapChar gpi_c1;
    gpi_MapChar gpi_c2;
    // = = = = = = = = = = = = = = = =

    if (gpi_py != 0)
    {
        gpi_c0 = this->gpi_map[gpi_px][gpi_py];
        gpi_c1 = this->gpi_map[gpi_px][gpi_py - 1];
        gpi_c2 = this->gpi_map[gpi_px][gpi_py - 2];

        // player -> floor
        // floor  -> player
        if (gpi_c0 == player && gpi_c1 == floor)
        {
            gpi_py -= 1;
            this->gpi_yPlayer = gpi_py;
            this->gpi_map[gpi_px][gpi_py + 1] = floor;
            this->gpi_map[gpi_px][gpi_py    ] = player;
            return;
        }

        // finPlayer -> floor
        // finish    -> player
        if (gpi_c0 == finPlayer && gpi_c1 == floor)
        {
            gpi_py -= 1;
            this->gpi_yPlayer = gpi_py;
            this->gpi_map[gpi_px][gpi_py + 1] = finish;
            this->gpi_map[gpi_px][gpi_py    ] = player;
            return;
        }

        // player -> box    -> floor
        // floor  -> player -> box
        if (gpi_c0 == player && gpi_c1 == box && gpi_c2 == floor)
        {
            gpi_py -= 1;
            this->gpi_yPlayer = gpi_py;
            this->gpi_map[gpi_px][gpi_py + 1] = floor;
            this->gpi_map[gpi_px][gpi_py    ] = player;
            this->gpi_map[gpi_px][gpi_py - 1] = box;
            return;
        }

        // finPlayer -> box    -> floor
        // finish    -> player -> box
        if (gpi_c0 == finPlayer && gpi_c1 == box && gpi_c2 == floor)
        {
            gpi_py -= 1;
            this->gpi_yPlayer = gpi_py;
            this->gpi_map[gpi_px][gpi_py + 1] = finish;
            this->gpi_map[gpi_px][gpi_py    ] = player;
            this->gpi_map[gpi_px][gpi_py - 1] = box;
            return;
        }

        // player -> box    -> finish
        // floor  -> player -> finBox
        if (gpi_c0 == player && gpi_c1 == box && gpi_c2 == finish)
        {
            gpi_py -= 1;
            this->gpi_yPlayer = gpi_py;
            this->gpi_map[gpi_px][gpi_py + 1] = floor;
            this->gpi_map[gpi_px][gpi_py    ] = player;
            this->gpi_map[gpi_px][gpi_py - 1] = finBox;
            return;
        }

        // finPlayer -> box    -> finish
        // finish    -> player -> finBox
        if (gpi_c0 == finPlayer && gpi_c1 == box && gpi_c2 == finish)
        {
            gpi_py -= 1;
            this->gpi_yPlayer = gpi_py;
            this->gpi_map[gpi_px][gpi_py + 1] = finish;
            this->gpi_map[gpi_px][gpi_py    ] = player;
            this->gpi_map[gpi_px][gpi_py - 1] = finBox;
            return;
        }

        // player -> finBox    -> floor
        // floor  -> finPlayer -> box
        if (gpi_c0 == player && gpi_c1 == finBox && gpi_c2 == floor)
        {
            gpi_py -= 1;
            this->gpi_yPlayer = gpi_py;
            this->gpi_map[gpi_px][gpi_py + 1] = floor;
            this->gpi_map[gpi_px][gpi_py    ] = finPlayer;
            this->gpi_map[gpi_px][gpi_py - 1] = box;
            return;
        }

        // finPlayer -> finBox    -> floor
        // finish    -> finPlayer -> box
        if (gpi_c0 == finPlayer && gpi_c1 == finBox && gpi_c2 == floor)
        {
            gpi_py -= 1;
            this->gpi_yPlayer = gpi_py;
            this->gpi_map[gpi_px][gpi_py + 1] = finish;
            this->gpi_map[gpi_px][gpi_py    ] = finPlayer;
            this->gpi_map[gpi_px][gpi_py - 1] = box;
            return;
        }

        // player -> finBox    -> finish
        // floor  -> finPlayer -> finBox
        if (gpi_c0 == player && gpi_c1 == finBox && gpi_c2 == finish)
        {
            gpi_py -= 1;
            this->gpi_yPlayer = gpi_py;
            this->gpi_map[gpi_px][gpi_py + 1] = floor;
            this->gpi_map[gpi_px][gpi_py    ] = finPlayer;
            this->gpi_map[gpi_px][gpi_py - 1] = finBox;
            return;
        }

        // finPlayer -> finBox    -> finish
        // finish    -> finPlayer -> finBox
        if (gpi_c0 == finPlayer && gpi_c1 == finBox && gpi_c2 == finish)
        {
            gpi_py -= 1;
            this->gpi_yPlayer = gpi_py;
            this->gpi_map[gpi_px][gpi_py + 1] = finish;
            this->gpi_map[gpi_px][gpi_py    ] = finPlayer;
            this->gpi_map[gpi_px][gpi_py - 1] = finBox;
            return;
        }

        // player -> finish
        // floor  -> finPlayer
        if (gpi_c0 == player && gpi_c1 == finish)
        {
            gpi_py -= 1;
            this->gpi_yPlayer = gpi_py;
            this->gpi_map[gpi_px][gpi_py + 1] = floor;
            this->gpi_map[gpi_px][gpi_py    ] = finPlayer;
            return;
        }

        // finPlayer -> finish
        // finish    -> finPlayer
        if (gpi_c0 == finPlayer && gpi_c1 == finish)
        {
            gpi_py -= 1;
            this->gpi_yPlayer = gpi_py;
            this->gpi_map[gpi_px][gpi_py + 1] = finish;
            this->gpi_map[gpi_px][gpi_py    ] = finPlayer;
            return;
        }
    }
}
