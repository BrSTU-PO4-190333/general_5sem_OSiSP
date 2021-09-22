#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::generate1Level()
{
    char StrMap[] ="\
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

    size_t StrMapLen = strlen(StrMap);
    for (int iter = 0, i = 0, j = 0; iter < StrMapLen; iter += 1)
    {

        if (StrMap[iter] == '\n')
        {
            j += 1;
            i = 0;
        }
        else if (i > (this->length))
        {
            continue;
        }
        else
        {
            switch(StrMap[iter])
            {
                case '.':
                    map[i][j] = floor;
                    break;
                case 'x':
                    map[i][j] = wall;
                    break;
                case '@':
                    map[i][j] = player;
                    this->xPlayer = i;
                    this->yPlayer = j;
                    break;
                case 'f':
                    map[i][j] = finish;
                    break;
                case 'A':
                    map[i][j] = finPlayer;
                    this->xPlayer = i;
                    this->yPlayer = j;
                    break;
                case 'b':
                    map[i][j] = box;
                    break;
                case 'B':
                    map[i][j] = finBox;
                    break;
                default:
                    map[i][j] = err;
                    break;
            }

            i += 1;
        }
    }
}
