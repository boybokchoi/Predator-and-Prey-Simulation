#ifndef PREDATOR_H
#define PREDATOR_H

#include "creature.h"
#include "gConst.h"
#include "coords.h"

/*
Description:

    Predator moves around and eats prey. Eating a prey means moving to the position of the prey.
    Breeds every 8 steps.

*/

class Predator: public Creature
{ 
public:
    Predator();
    Predator(Coords c, Creature*** Grd);

    Coords WhereEat();    //checks whether or not there is anything around to eat.
    void Die();

    //virtual
    void Move();
    void Breed();

};

#endif // PREDATOR_H
