#include "gpi_gamewindow.hpp"
#include "ui_gpi_gamewindow.h"

void gpi_GameWindow::gpi_goRight ()
{
    int         gpi_l           = this->gpi_length;
    int         gpi_px          = this->gpi_xPlayer;
    int         gpi_py          = this->gpi_yPlayer;
    gpi_MapChar gpi_c0;
    gpi_MapChar gpi_c1;
    gpi_MapChar gpi_c2;
    // = = = = = = = = = = = = = = = =

    if (gpi_px != gpi_l - 1)
    {
        gpi_c0 = this->gpi_map[gpi_px    ][gpi_py];
        gpi_c1 = this->gpi_map[gpi_px + 1][gpi_py];
        gpi_c2 = this->gpi_map[gpi_px + 2][gpi_py];

        // player -> floor
        // floor  -> player
        if (gpi_c0 == player && gpi_c1 == floor)
        {
            gpi_px += 1;
            this->gpi_xPlayer = gpi_px;
            this->gpi_map[gpi_px - 1][gpi_py] = floor;
            this->gpi_map[gpi_px    ][gpi_py] = player;
            return;
        }

        // finPlayer -> floor
        // finish    -> player
        if (gpi_c0 == finPlayer && gpi_c1 == floor)
        {
            gpi_px += 1;
            this->gpi_xPlayer = gpi_px;
            this->gpi_map[gpi_px - 1][gpi_py] = finish;
            this->gpi_map[gpi_px    ][gpi_py] = player;
            return;
        }

        // player -> box    -> floor
        // floor  -> player -> box
        if (gpi_c0 == player && gpi_c1 == box && gpi_c2 == floor)
        {
            gpi_px += 1;
            this->gpi_xPlayer = gpi_px;
            this->gpi_map[gpi_px - 1][gpi_py] = floor;
            this->gpi_map[gpi_px    ][gpi_py] = player;
            this->gpi_map[gpi_px + 1][gpi_py] = box;
            return;
        }

        // finPlayer -> box    -> floor
        // finish    -> player -> box
        if (gpi_c0 == finPlayer && gpi_c1 == box && gpi_c2 == floor)
        {
            gpi_px += 1;
            this->gpi_xPlayer = gpi_px;
            this->gpi_map[gpi_px - 1][gpi_py] = finish;
            this->gpi_map[gpi_px    ][gpi_py] = player;
            this->gpi_map[gpi_px + 1][gpi_py] = box;
            return;
        }

        // finPlayer -> finBox -> floor
        // finish    -> finPlayer -> box
        if (gpi_c0 == finPlayer && gpi_c1 == finBox && gpi_c2 == floor)
        {
            gpi_px += 1;
            this->gpi_xPlayer = gpi_px;
            this->gpi_map[gpi_px - 1][gpi_py] = finish;
            this->gpi_map[gpi_px    ][gpi_py] = finPlayer;
            this->gpi_map[gpi_px + 1][gpi_py] = box;
            return;
        }

        // player -> finBox    -> floor
        // floor  -> finPlayer -> box
        if (gpi_c0 == player && gpi_c1 == finBox && gpi_c2 == floor)
        {
            gpi_px += 1;
            this->gpi_xPlayer = gpi_px;
            this->gpi_map[gpi_px - 1][gpi_py] = floor;
            this->gpi_map[gpi_px    ][gpi_py] = finPlayer;
            this->gpi_map[gpi_px + 1][gpi_py] = box;
            return;
        }

        // player -> box    -> finish
        // floor  -> player -> finBox
        if (gpi_c0 == player && gpi_c1 == box && gpi_c2 == finish)
        {
            gpi_px += 1;
            this->gpi_xPlayer = gpi_px;
            this->gpi_map[gpi_px - 1][gpi_py] = floor;
            this->gpi_map[gpi_px    ][gpi_py] = player;
            this->gpi_map[gpi_px + 1][gpi_py] = finBox;
            return;
        }

        // finPlayer -> box    -> finish
        // finish    -> player -> finBox
        if (gpi_c0 == finPlayer && gpi_c1 == box && gpi_c2 == finish)
        {
            gpi_px += 1;
            this->gpi_xPlayer = gpi_px;
            this->gpi_map[gpi_px - 1][gpi_py] = finish;
            this->gpi_map[gpi_px    ][gpi_py] = player;
            this->gpi_map[gpi_px + 1][gpi_py] = finBox;
            return;
        }

        // player -> finBox    -> finish
        // floor  -> finPlayer -> finBox
        if (gpi_c0 == player && gpi_c1 == finBox && gpi_c2 == finish)
        {
            gpi_px += 1;
            this->gpi_xPlayer = gpi_px;
            this->gpi_map[gpi_px - 1][gpi_py] = floor;
            this->gpi_map[gpi_px    ][gpi_py] = finPlayer;
            this->gpi_map[gpi_px + 1][gpi_py] = finBox;
            return;
        }

        // finPlayer -> finBox    -> finish
        // finish    -> finPlayer -> finBox
        if (gpi_c0 == finPlayer && gpi_c1 == finBox && gpi_c2 == finish)
        {
            gpi_px += 1;
            this->gpi_xPlayer = gpi_px;
            this->gpi_map[gpi_px - 1][gpi_py] = finish;
            this->gpi_map[gpi_px    ][gpi_py] = finPlayer;
            this->gpi_map[gpi_px + 1][gpi_py] = finBox;
            return;
        }

        // player -> finish
        // floor  -> finPlayer
        if (gpi_c0 == player && gpi_c1 == finish)
        {
            gpi_px += 1;
            this->gpi_xPlayer = gpi_px;
            this->gpi_map[gpi_px - 1][gpi_py] = floor;
            this->gpi_map[gpi_px    ][gpi_py] = finPlayer;
            return;
        }

        // finPlayer -> finish
        // finish    -> finPlayer
        if (gpi_c0 == finPlayer && gpi_c1 == finish)
        {
            gpi_px += 1;
            this->gpi_xPlayer = gpi_px;
            this->gpi_map[gpi_px - 1][gpi_py] = finish;
            this->gpi_map[gpi_px    ][gpi_py] = finPlayer;
            return;
        }
    }
}
