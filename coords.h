#ifndef COORDS_H
#define COORDS_H

#include <iostream>
using namespace std;

class Creature;
class Grid;

class Coords
{
public:
    Coords();
    Coords(int X, int Y);

    //overload operators for generic use
    friend bool operator ==(const Coords& LHS, const Coords& RHS);
    friend bool operator !=(const Coords& LHS, const Coords& RHS);
    friend ostream& operator <<(ostream& outs, const Coords& c);

    int x, y; //coordinates
};

#endif // COORDS_H
