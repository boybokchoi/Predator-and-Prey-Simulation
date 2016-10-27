#include "bomber.h"
#include "gConst.h"
#include "coords.h"
#include "grid.h"
#include "creature.h"

Bomber::Bomber()
{
}

Bomber::Bomber(Coords c, Creature ***Grd)
{
    steps = 0;
    breedSteps = 0;
    bombSteps = 0;
    pos = c;
    face = BOMBER;
    flag = false;
    crGrid = Grd;
}

void Bomber::Move()
{
    Coords hold = pos;

    if(flag == false)       //if already moved
    {
        Explode();
        return;
    }

    Coords moveTo = FreeLoc();

    if(moveTo == NEGPOS)    //if position doesn't exist or already moved
    {
        flag = false;
        Explode();
        bombSteps++;
        return;
    }

    //switch x and y because x is the columns, and y is the rows.
    pos = moveTo;

    delete crGrid[pos.y][pos.x];                    //free memory of new location
    crGrid[pos.y][pos.x] = new Bomber;
    crGrid[pos.y][pos.x] = crGrid[hold.y][hold.x];  //point new Bomber to old Bomber
    crGrid[hold.y][hold.x] = NULL;                  //set old pointer to NULL.
    crGrid[pos.y][pos.x]->flag = false;             //This object has moved.

    Explode();      //call Explode
    steps++;
    bombSteps++;    //increment # of steps until explosion
}

void Bomber::Breed()
{
    //Bomber breeds every 10 steps
    if(breedSteps >= 10)
    {
        Coords newBombAt = FreeLoc();
        if(newBombAt == NEGPOS)
        {
            //cout << "NO PLACES TO CREATE NEW BOMB." << endl;
            return;
        }

        //IF new location is NULL, generate a new Bomber.
        if(crGrid[newBombAt.y][newBombAt.x] == NULL)
        {
            crGrid[newBombAt.y][newBombAt.x] = new Bomber(newBombAt, crGrid);
            breedSteps = 0;
            return;
        }
    }

    breedSteps++;
    //cout << pos << "->breedSteps:: " << breedSteps << endl;
}

void Bomber::Explode()
{
    int iStart(0), jStart(0), iEnd(0), jEnd(0);

    int i = pos.y;
    int j = pos.x;

    //Explosion destroys in a radius of 2
    iStart = i-2;
    iEnd = i+2;
    jStart = j-2;
    jEnd = j+2;

    //in case boundaries are passed
    if(iStart < 0)
        iStart = i;
    if(jStart < 0)
        jStart = j;

    if(iEnd >= X_SIZE)
        iEnd = i;
    if(jEnd >= Y_SIZE)
        jEnd = j;

    //Sets everything around it, AND itself to NULL EVERY 30 steps.
    if(bombSteps == 30)
    {
        for(int col = iStart; col <= iEnd; col++)
        {
            for(int row = jStart; row <= jEnd; row++)
            {
                //crGrid, backwards because columns are x, and rows are y.
                if((crGrid[col][row] != NULL) && ((crGrid[col][row]->face) != PREDATOR)
                                                && (crGrid[col][row]->face != GOD))
                {
                    crGrid[col][row] = NULL;
                    delete crGrid[col][row];
                }
            }
        }
        //reset bombSteps
        bombSteps = 0;
     }
}
