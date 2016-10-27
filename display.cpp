#include "display.h"
#include "grid.h"
#include "gConst.h"

#include <iostream>
using namespace std;

Display::Display(char** b)
{
    board = b;
}

void Display::Show()
{

    cout << "                           PREDATOR & PREY." << endl;

    for(int i = 0; i < X_SIZE; i++)
    {
        cout << "                 ";

        for(int j = 0; j < Y_SIZE; j++)
        {
            cout << board[i][j] << " ";
        }

        cout << endl;
    }
}
