#include "GameSokoban/GameSokoban.hpp"

int main()
{
    GameSokoban object = GameSokoban();
    while (1)
    {
        system("cls");
        object.printMap();
        int ch = _getch();
        switch (ch)
        {
        case 'w':
        case 'W':
            object.goTop();
            break;

        case 'd':
        case 'D':
            object.goRight();
            break;

        case 's':
        case 'S':
            object.goBottom();
            break;

        case 'a':
        case 'A':
            object.goLeft();
            break;

        default:
            break;
        }
    }
}
