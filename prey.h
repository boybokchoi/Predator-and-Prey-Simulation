#ifndef PREY_H
#define PREY_H

#include "creature.h"

/*
Description:

    Prey doesn't do anything except move and breed every 3 steps.

*/
class Prey: public Creature
{
public:
    Prey();
    Prey(Coords c, Creature*** Grd);

    //virtual
    void Move();
    void Breed();


};

#endif // PREY_H
