#include "gpi_gamewindow.hpp"
#include "ui_gpi_gamewindow.h"

void gpi_GameWindow::gpi_generateLevel1 ()
{
    int         gpi_iter;
    int         gpi_i;
    int         gpi_j;
    int         gpi_l           = this->gpi_length;
    char        gpi_strMap[]    = "\
xxxxxxxxxxxxxxx\n\
xxxxxxxxxxxxxxx\n\
xxxxxxxxxxxxxxx\n\
xxxxxxxxxxxxxxx\n\
xxxxxx...xxxxxx\n\
xxxxf@b..xxxxxx\n\
xxxxxx.bfxxxxxx\n\
xxxxfxxb.xxxxxx\n\
xxxx.x.f.xxxxxx\n\
xxxxb.Bbbfxxxxx\n\
xxxx...f..xxxxx\n\
xxxxxxxxxxxxxxx\n\
xxxxxxxxxxxxxxx\n\
xxxxxxxxxxxxxxx\n\
xxxxxxxxxxxxxxx\n\
";
    int         gpi_strMapLen   = strlen(gpi_strMap);
    // = = = = = = = = = = = = = = = =

    gpi_iter = 0;
    gpi_i = 0;
    gpi_j = 0;
    while (gpi_iter < gpi_strMapLen)
    {
        if (gpi_strMap[gpi_iter] == '\n')
        {
            ++gpi_j;
            gpi_i = 0;
        }
        else if (gpi_i > gpi_l)
        {
            continue;
        }
        else
        {
            switch(gpi_strMap[gpi_iter])
            {
                case '.':
                    this->gpi_map[gpi_i][gpi_j] = floor;
                    break;
                case 'x':
                    this->gpi_map[gpi_i][gpi_j] = wall;
                    break;
                case '@':
                    this->gpi_map[gpi_i][gpi_j] = player;
                    this->gpi_xPlayer = gpi_i;
                    this->gpi_yPlayer = gpi_j;
                    break;
                case 'f':
                    this->gpi_map[gpi_i][gpi_j] = finish;
                    break;
                case 'A':
                    this->gpi_map[gpi_i][gpi_j] = finPlayer;
                    this->gpi_xPlayer = gpi_i;
                    this->gpi_yPlayer = gpi_j;
                    break;
                case 'b':
                    this->gpi_map[gpi_i][gpi_j] = box;
                    break;
                case 'B':
                    this->gpi_map[gpi_i][gpi_j] = finBox;
                    break;
                default:
                    this->gpi_map[gpi_i][gpi_j] = err;
                    break;
            }
            ++gpi_i;
        }
        ++gpi_iter;
    }
}
