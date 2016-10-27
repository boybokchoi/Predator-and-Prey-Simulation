#ifndef CREATURE_H
#define CREATURE_H

#include "gConst.h"
#include "coords.h"

class Creature
{
public:
    //Constructor
    Creature();
    Creature(Coords c);
    Creature(char f, Coords c, Creature*** Grd);
    ~Creature();

    virtual void Move() //for child classes
    {
        //cout << endl << "Creature Move called." << endl;
    }

    Coords FreeLoc(); //generates free position

    virtual void Breed()
    {
       // cout << endl << "Creature Breed called." << endl;
    }
    virtual void Die()
    {
        //cout << endl << "Creature Die called." << endl;
    }

    int steps;                      //keeps track of steps
    int breedSteps, starveSteps;    //steps before breeding/starving
    Coords pos;                     //position of creature
    char face;                      //what the creature looks like
    bool flag;                      //whether or not creature has moved;
    Creature*** crGrid;             //hold position of other creatures and surroundings

    friend class Grid;
};

#endif // CREATURE_H
