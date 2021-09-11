#include "GameSokoban.hpp"

GameSokoban::GameSokoban()
{
    map = new char* [sizeY];
    for (int i = 0; i < sizeY; i++)
    {
        map[i] = new char[sizeX];
    }

    generateEmptyMap();
    generateBorder();
    printPerson();
    map[X][Y] = '@';
    map[4][4] = '#';
    map[4][5] = '*';
}

GameSokoban::~GameSokoban()
{
    for (int i = 0; i < sizeY; i++)
    {
        delete[] map[i];
    }
    delete[] map;
}

void GameSokoban::generateEmptyMap()
{
    for (int i = 0; i < sizeY; i++)
    {
        for (int j = 0; j < sizeX; j++)
        {
            map[i][j] = '.';
        }
    }
}

void GameSokoban::generateBorder()
{
    for (int i = 0; i < sizeY; i++)
    {
        map[i][0] = '#';            //border-left
        map[i][sizeX - 1] = '#';    //border-right
    }

    for (int j = 0; j < sizeX; j++)
    {
        map[0][j] = '#';            //border-top
        map[sizeY - 1][j] = '#';    //border-bottom
    }
}

void GameSokoban::printMap()
{
    printf("Steps: %d\n", counter);
    for (int i = 0; i < sizeY; i++)
    {
        for (int j = 0; j < sizeX; j++)
        {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}

void GameSokoban::printPerson()
{
    map[Y][X] = '@';
    counter += 1;
}

void GameSokoban::goRight()
{
    printf("right");
    if (X != sizeX - 1)
    {
        if (map[Y][X + 1] == '*' && map[Y][X + 2] == '.')
        {
            X += 1;
            map[Y][X - 1] = '.';
            printPerson();
            map[Y][X + 1] = '*';
            return;
        }

        if (map[Y][X + 1] == '*' && map[Y][X + 2] == '#')
        {
            return;
        }

        if (map[Y][X + 1] != '#')
        {
            X += 1;
            map[Y][X - 1] = '.';
            printPerson();
            return;
        }
    }
}

void GameSokoban::goLeft()
{
    printf("left");
    if (X != 0)
    {
        if (map[Y][X - 1] == '*' && map[Y][X - 2] == '.')
        {
            X -= 1;
            map[Y][X + 1] = '.';
            printPerson();
            map[Y][X - 1] = '*';
            return;
        }

        if (map[Y][X - 1] == '*' && map[Y][X - 2] == '#')
        {
            return;
        }

        if (map[Y][X - 1] != '#')
        {
            X -= 1;
            map[Y][X + 1] = '.';
            printPerson();
            return;
        }
    }
}

void GameSokoban::goTop()
{
    printf("top");
    if (Y != 0)
    {
        if (map[Y - 1][X] == '*' && map[Y - 2][X] == '.')
        {
            Y -= 1;
            map[Y + 1][X] = '.';
            printPerson();
            map[Y - 1][X] = '*';
            return;
        }

        if (map[Y - 1][X] == '*' && map[Y - 2][X] == '#')
        {
            return;
        }

        if (map[Y - 1][X] != '#')
        {
            Y -= 1;
            map[Y + 1][X] = '.';
            printPerson();
        }
    }
}

void GameSokoban::goBottom()
{
    printf("bottom");
    if (Y != sizeY - 1)
    {
        if (map[Y + 1][X] == '*' && map[Y + 2][X] == '.')
        {
            Y += 1;
            map[Y - 1][X] = '.';
            printPerson();
            map[Y + 1][X] = '*';
            return;
        }

        if (map[Y + 1][X] == '*' && map[Y + 2][X] == '#')
        {
            return;
        }

        if (map[Y + 1][X] != '#')
        {
            Y += 1;
            map[Y - 1][X] = '.';
            printPerson();
            return;
        }
    }
}
