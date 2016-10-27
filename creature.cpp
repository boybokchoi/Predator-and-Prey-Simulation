#include "creature.h"
#include "coords.h"
#include "gConst.h"
#include "random.h"

#include <iostream>
using namespace std;

Creature::Creature()
{
    steps = 0;
    pos = Coords(0,0);
    face = ' ';
    flag = false;
}

Creature::Creature(Coords c)
{
    pos = c;
    steps = 0;
    face = ' ';
    flag = false;
}

Creature::Creature(char f, Coords c, Creature*** Grd)
{
    pos = c;
    face = f;
    steps = 0;
    crGrid = Grd;
    flag = false;
}

Creature::~Creature()
{
    for(int i = 0; i < Y_SIZE; i++)
    {
        delete[] crGrid[i];
    }

    delete[] crGrid;
}

Coords Creature::FreeLoc()
{
    Coords freePos[9]; //9 is total number of free spaces
    Coords neg(-1,-1);
    Coords newPos;

    int random(0), randCount(0), count(0), iStart(0), jStart(0), iEnd(0), jEnd(0);

    //fill with (NEGPOS)
    for(int i = 0; i < 9; i++)
    {
        freePos[i] = Coords(-1,-1);
    }

    int i = pos.y;
    int j = pos.x;
    iStart = i-1;
    iEnd = i+1;
    jStart = j-1;
    jEnd = j+1;

    //CHECK BOUNDARIES.
    if(iStart < 0)
        iStart = i;
    if(jStart < 0)
        jStart = j;

    if(iEnd >= X_SIZE)
        iEnd = i;
    if(jEnd >= Y_SIZE)
        jEnd = j;


    //look for open positions and store in array(freePos)
    for(int col = iStart; col <= iEnd; col++)
    {
        for(int row = jStart; row <= jEnd; row++)
        {
            //crGrid, backwards because columns are x, and rows are y.
            if(crGrid[col][row] == NULL)
            {
                //store available position IN array of Coords.
                freePos[count] = Coords(row, col);
                count++;
                randCount++;   //size of array
            }
        }
    }

    Random r;
    random = r.GenRand(randCount); //generate a random index

    if(freePos[random] == NEGPOS)  //no available free spaces
        return NEGPOS;

    return freePos[random];
}
