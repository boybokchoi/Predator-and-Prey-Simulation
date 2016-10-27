#include "prey.h"
#include "gConst.h"
#include "coords.h"
#include "grid.h"
#include "creature.h"

#include <iostream>
using namespace std;

Prey::Prey()
{
}

Prey::Prey(Coords c, Creature*** Grd)
{
    steps = 0;
    breedSteps = 0;
    pos = c;
    face = PREY;
    flag = false;
    crGrid = Grd;
}

void Prey::Move()
{
    Coords hold = pos;

    //IF already moved
    if(flag == false)
    {
        return;
    }

    Coords moveTo = FreeLoc();

    if(moveTo == NEGPOS)   //if position doesn't exist or already moved
    {
        flag = false;
        return;
    }


    pos = moveTo;

    //switch x and y because x is the columns, and y is the rows.
    crGrid[pos.y][pos.x] = crGrid[hold.y][hold.x];
    crGrid[hold.y][hold.x] = NULL;

    crGrid[pos.y][pos.x]->flag = false;

    steps++;
}

void Prey::Breed()
{
    Coords newPreyAt = FreeLoc();

    //BREEDS every 3 steps and if there is free space
    if(breedSteps >= 3)
    {
        //nowhere to breed
        if(newPreyAt == NEGPOS)
        {
            return;
        }
        //if FREE space, create new Predator
        if(crGrid[newPreyAt.y][newPreyAt.x] == NULL)
        {
            delete crGrid[newPreyAt.y][newPreyAt.x];
            crGrid[newPreyAt.y][newPreyAt.x] = new Prey(newPreyAt, crGrid);
            breedSteps = 0;
            return;
        }
    }

    //increment breedSteps IF there was nowhere to breed
    if(newPreyAt != NEGPOS)
        breedSteps++;
}
