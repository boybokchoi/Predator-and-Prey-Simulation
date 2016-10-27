#include "coords.h"

Coords::Coords()
{
    //because even 0,0 is a valid position
    x = -1;
    y = -1;
}

Coords::Coords(int X, int Y)
{
    x = X;
    y = Y;
}

bool operator ==(const Coords& LHS, const Coords& RHS)
{
    if((LHS.x == RHS.x)&&(LHS.y == RHS.y))
        return true;
    else
        return false;
}

bool operator !=(const Coords& LHS, const Coords& RHS)
{
    if((LHS.x != RHS.x)||(LHS.y != RHS.y))
        return true;
    else
        return false;
}

 ostream& operator << (ostream& outs, const Coords& c)
 {
     outs << "(" << c.x << "," << c.y << ")";
     return outs;
 }
