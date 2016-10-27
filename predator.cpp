#include "predator.h"
#include "gConst.h"
#include "coords.h"
#include "random.h"

Predator::Predator()
{
}

Predator::Predator(Coords c, Creature*** Grd)
{
    steps = 0;
    starveSteps = 0;
    breedSteps = 0;
    pos = c;
    face = PREDATOR;
    flag = false;
    crGrid = Grd;
}

void Predator::Move()
{
    Coords hold = pos;

    //IF already moved, skip.
    if(flag == false)
    {
        //cout << endl << "flag == false. Skipping." << endl;
        return;
    }

    //looks for Prey around it.
    Coords eatAt = WhereEat();

    //Something to eat around it, will move to the loc of prey.
    if(eatAt != NEGPOS)
    {
        pos = eatAt;

        //replace new position with creature of old pos; set old to NULL
        crGrid[pos.y][pos.x] = crGrid[hold.y][hold.x];
        crGrid[hold.y][hold.x] = NULL;
        delete crGrid[hold.y][hold.x];

        crGrid[pos.y][pos.x]->flag = false;

        steps++;
        starveSteps = 0;
        return;
    }

    //IF no prey around, just normal move.

    Coords moveTo = FreeLoc();

    if(moveTo == NEGPOS)   //if position doesn't exist or already moved
    {
        flag = false;
        return;
    }

    pos = moveTo;
    //switch x and y because x is the columns, and y is the rows.
    crGrid[pos.y][pos.x] = new Predator;
    crGrid[pos.y][pos.x] = crGrid[hold.y][hold.x];
    crGrid[hold.y][hold.x] = NULL;

    crGrid[pos.y][pos.x]->flag = false;

    steps++;
    starveSteps++; //hasn't eaten
}

void Predator::Breed()
{
    //EVERY 8 steps, breeds at random free location
    if(breedSteps >= 8)
    {
        Coords newPredAt = FreeLoc();

        //NO free location around
        if(newPredAt == NEGPOS)
        {
            return;
        }

        //IF free position around, move Predator to freePos
        if(crGrid[newPredAt.y][newPredAt.x] == NULL)
        {
            delete[] crGrid[newPredAt.y][newPredAt.x];
            crGrid[newPredAt.y][newPredAt.x] = new Predator(newPredAt, crGrid);
            breedSteps = 0;
            return;
        }
    }

    breedSteps++;
    //cout << pos << "->breedSteps:: " << breedSteps << endl;
}

Coords Predator::WhereEat()
{
    Coords toEat[4];        //4 accounts for north, west, east, south
    Coords neg(-1,-1);
    Coords newPos;

    int random(0), randCount(0), count(0), iStart(0), jStart(0), iEnd(0), jEnd(0);

    for(int i = 0; i < 4; i++)
    {
        toEat[i] = Coords(-1,-1);
    }

    int i = pos.y;
    int j = pos.x;
    iStart = i-1;
    iEnd = i+1;
    jStart = j-1;
    jEnd = j+1;

    //CHECKING BOUNDARIES
    if(iStart < 0)
        iStart = i;
    if(jStart < 0)
        jStart = j;

    if(iEnd >= X_SIZE)
        iEnd = i;
    if(jEnd >= Y_SIZE)
        jEnd = j;

    //Coords of north, west, east, south
    Coords n(iStart, j);
    Coords w(i, jStart);
    Coords e(i, jEnd);
    Coords s(iEnd, j);

    //look for open positions and store in array(toEat)
    for(int col = iStart; col <= iEnd; col++)
    {
        for(int row = jStart; row <= jEnd; row++)
        {
            //crGrid, backwards because columns are x, and rows are y.
            if((crGrid[col][row] != NULL) && (crGrid[col][row] != crGrid[pos.y][pos.x]))
            {
                if(crGrid[col][row]->face == PREY)
                {
                    Coords c(col, row);
                    //IF there is prey north, west, east, or south of predator store in toEat array
                    if((c == n) || (c == w) || (c == e) || (c == s))
                    {
                        toEat[count] = Coords(row, col);
                        count++;
                        randCount++;
                    }
                }
            }
        }
    }
    Random r;
    random = r.GenRand(randCount);

    //no Prey north, west, east, or south of pred
    if(toEat[random] == NEGPOS)
        return NEGPOS;

    return toEat[random];
}

void Predator::Die()
{
    //if haven't eaten for 3 steps, dies.
    if(starveSteps == 3)
    {
        crGrid[pos.y][pos.x] = NULL;
    }
}
