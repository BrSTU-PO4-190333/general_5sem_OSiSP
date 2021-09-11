#pragma once

#include <iostream>
#include <conio.h>
using namespace std;

class GameSokoban
{
    // '@' - Player cell
    // '#' - Wall cell
    // '*' - Cell with box
    // '.' - Empty cell

    private:
        const int sizeX = 15;
        const int sizeY = 15;
        char** map;
        int X = 1;
        int Y = 1;
        int counter = -1;

        void generateEmptyMap();
        void generateBorder();
        void printPerson();

    public:
        GameSokoban();
        ~GameSokoban();
        void printMap();
        void goLeft();
        void goRight();
        void goTop();
        void goBottom();
};
