#include "helpers.h"

void clear() {
    system("cls");
}

void pause() {
    _getch();
}

void update(int& press) {
    press = 0;
    clear();
}

void gotoxy(int X, int Y)
{
    COORD coord = { X, Y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}