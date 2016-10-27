#include "bomber.h"
#include "prey.h"
#include "predator.h"
#include "gConst.h"
#include "coords.h"
#include "grid.h"
#include "creature.h"
#include "random.h"
#include "god.h"

God::God()
{
}

God::God(Coords c, Creature ***Grd)
{
    steps = 0;
    breedSteps = 0;
    pos = c;
    face = GOD;
    flag = false;
    crGrid = Grd;
}

void God::Move()
{
    Create();
    steps++;
}

void God::Create()
{
    int iStart(0), jStart(0), iEnd(0), jEnd(0);

    int i = pos.y;
    int j = pos.x;
    //destroys everything in a 50 unit radius.
    iStart = i-50;
    iEnd = i+50;
    jStart = j-50;
    jEnd = j+50;


    Coords freeSpace = FreeLoc();

    //IF NO OPEN SPACE, destroys everything and more around it.
    //OR after 100 steps
    if(freeSpace == NEGPOS || (steps == 100))
    {
        //cout << "NO FREE SPACE FOR GOD." << endl;
        for(int col = iStart; col <= iEnd; col++)
        {
             for(int row = jStart; row <= jEnd; row++)
             {
                 //crGrid, backwards because columns are x, and rows are y.
                 //if its already NULL, we don't need to set it to NULL again
                 if(crGrid[col][row] == NULL)
                 {
                     //do nothing
                 }
                 else if(crGrid[col][row]->face != GOD)
                 {
                     crGrid[col][row] = NULL;
                 }
             }
         }

        steps = 0;
        return;
    }

    //Generate creatures AROUND god creature
    iStart = i-1;
    iEnd = i+1;
    jStart = j-1;
    jEnd = j+1;

    Random r;

    //In any open space around it, creates random creatures.
    for(int col = iStart; col <= iEnd; col++)
    {
         for(int row = jStart; row <= jEnd; row++)
         {
             //crGrid, backwards because columns are x, and rows are y.
             if(crGrid[col][row] == NULL)
             {
                 Coords c(row, col);

                 //Only uses 1,2,or 3 to generate prey, pred, or bomber.
                 //Other numbers will do nothing, to simulate more randomness.
                 int randNum = r.GenRand(8);

                 if(randNum == 1)
                 {
                     crGrid[col][row] = new Prey(c, crGrid);
                 }
                 else if(randNum == 2)
                 {
                     crGrid[col][row] = new Predator(c, crGrid);
                 }
                 else if(randNum == 3)
                 {
                     crGrid[col][row] = new Bomber(c, crGrid);
                 }
             }
         }
     }
}
