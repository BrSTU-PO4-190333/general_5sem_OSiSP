#include <iostream>
#include <conio.h>
using namespace std;

const int sizeX = 15;
const int sizeY = 15;
char map[sizeY][sizeX];
int X = 1;
int Y = 1;

void generateEmptyMap();
void generateBorder();
void printMap();
void printPerson();
void goLeft();
void goRight();
void goTop();
void goBottom();

int main()
{
    generateEmptyMap();
    generateBorder();
    map[X][Y] = '@';
    while (1)
    {
        system("cls");
        printMap();
        printPerson();
        int ch = _getch();
        switch (ch)
        {
        case 'd': goRight(); break;
        case 'a': goLeft(); break;
        case 's': goBottom(); break;
        case 'w': goTop(); break;
        default: printf("q");
        }
    }
}

void generateEmptyMap()
{
    for (int i = 0; i < sizeY; i++)
    {
        for (int j = 0; j < sizeX; j++)
        {
            map[i][j] = '.';
        }
    }
}

void generateBorder()
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

void printMap()
{
    for (int i = 0; i < sizeY; i++)
    {
        for (int j = 0; j < sizeX; j++)
        {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}

void printPerson()
{
    map[Y][X] = '@';
}

void goRight()
{
    printf("right");
    if (X != sizeX - 1 - 1)
    {
        X += 1;
        map[Y][X - 1] = '.';
        printPerson();
    }
}

void goLeft()
{
    printf("left");
    if (X != 1)
    {
        X -= 1;
        map[Y][X + 1] = '.';
        printPerson();
    }
}

void goTop()
{
    printf("top");
    if (Y != 1)
    {
        Y -= 1;
        map[Y + 1][X] = '.';
        printPerson();
    }
}

void goBottom()
{
    printf("bottom");
    if (Y != sizeY - 1 - 1)
    {
        Y += 1;
        map[Y - 1][X] = '.';
        printPerson();
    }
}
