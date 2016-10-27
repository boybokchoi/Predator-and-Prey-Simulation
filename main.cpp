#include "creature.h"
#include "predator.h"
#include "prey.h"
#include "grid.h"
#include "display.h"
#include "gConst.h"
#include "random.h"
#include "draw.h"
#include "god.h"

#include <windows.h>
#include <iostream>
#include <QApplication>
#include <QDesktopWidget>
using namespace std;

void Info();

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Grid G;
    Draw graphics;

    Info();
    graphics.show();

    cout << endl << endl << "PROGRAM COMPLETE." << endl;

    return app.exec();

    return 0;
}

void Info()
{
    cout << "===========================CREATURE DESCRIPTIONS==============================" << endl << endl;
    cout << "Red squares: Bombers.\n"
         << "Explode after a certain # of turns and kills surrounding Prey.\n"
         << "Breeds every 10 steps." << endl << endl;

    cout << "Cyan squares: Prey. No special function.\n"
         << "Breeds after 3 steps." << endl << endl;

    cout << "Purple squares: Predator. Eats Prey.\n"
         <<  "Dies if hasn't eaten for 3 steps.\n"
         << "Breeds every 8 steps." << endl << endl;

    cout << "Green square: GOD. Doesn't move, stays in middle of grid.\n"
         << "Generates random creatures at random.\n"
         << "If completely surrounded, destroys everything around it in a 50 unit radius." << endl;

}
