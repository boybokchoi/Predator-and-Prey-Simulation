#ifndef BOMBER_H
#define BOMBER_H

#include "creature.h"

/*
Description:

    Bomber moves like a prey, in any direction that it can. Every 10 steps, it breeds.
    However, after 30 steps, it will explode, destroying any PREY around it.

*/

class Bomber: public Creature
{
public:
    Bomber();
    Bomber(Coords c, Creature*** Grd);

    void Move();     //Moves in free locations around it
    void Breed();    //breeds every 10 steps
    void Explode();  //destroys surrounding creatures

    int bombSteps;   //counts how long until the bomber explodes
};

#endif // BOMBER_H
