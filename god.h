#ifndef GOD_H
#define GOD_H

#include "creature.h"

/*
Description:

    God doesn't move OR breed. It is placed in the middle of the grid. Generates random creatures around it.
    If there is no space to generate creatures, it destroys everything around it in a 50 unit radius.

*/

class God: public Creature
{
public:
    God();
    God(Coords c, Creature*** Grd);

    void Move();    //Doesn't actually move, just calls create
    void Create();  //generates random creatures around and destroys if there are no free spaces around
};

#endif // GOD_H
