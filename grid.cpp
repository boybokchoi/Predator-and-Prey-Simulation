#include "grid.h"
#include "creature.h"
#include "prey.h"
#include "predator.h"
#include "bomber.h"
#include "god.h"
#include "gConst.h"
#include "random.h"

#include <iostream>
using namespace std;

Grid::Grid()
{
    snapShot = new char*[X_SIZE];

    //set everything inside of Grid to NULL.
    //also create rows for snapShot

    grid = new Creature**[X_SIZE];

    for(int i = 0; i < X_SIZE; i++)
    {
        grid[i] = new Creature*[X_SIZE];
        snapShot[i] = new char[X_SIZE];

        for(int j = 0; j < Y_SIZE; j++)
        {
            grid[i][j] = NULL;
        }
    }
    //Add initial creatures
    InitCreat();

    SnapShot();
    total = 0;
}

Grid::Grid(Coords c)
{
    snapShot = new char*[X_SIZE];
    grid = new Creature**[X_SIZE];

    for(int i = 0; i < X_SIZE; i++)
    {
        grid[i] = new Creature*[X_SIZE];
        snapShot[i] = new char[X_SIZE];

        for(int j = 0; j < Y_SIZE; j++)
        {
            grid[i][j] = NULL;
        }
    }

    SnapShot();
    total = 0;
}

Grid::~Grid()
{
    for(int i = 0; i < Y_SIZE; i++)
    {
        delete[] grid[i];
        delete[] snapShot[i];
    }

    delete[] grid;
    delete[] snapShot;
}

void Grid::SnapShot()
{
    total = 0;
    for(int i = 0; i < X_SIZE; i++)
    {
        for(int j = 0; j < Y_SIZE; j++)
        {
            if(grid[i][j] == NULL)
            {
                snapShot[i][j] = '.';
            }
            else
            {
                snapShot[i][j] = grid[i][j]->face;
                total++;
            }
        }

        snapShot[i][X_SIZE-1] = NULL; //make sure end of each pointer is NULL.
    }
}

char Grid::GetFace(Coords c)
{
    char face;



    if(grid[c.y][c.x] == NULL)
    {
        face = EMPTY;
        return face;
    }
    else
        face = grid[c.y][c.x]->face;

    return face;
}

void Grid::Move()
{
    //cout << "Grid::Move() called." << endl;

    //set all available creature flags to TRUE.
    for(int i = 0; i < X_SIZE; i++)
    {
        for(int j = 0; j < Y_SIZE; j++)
        {
            if(grid[i][j] != NULL)
            {
                grid[i][j]->flag = true;
            }
        }
    }

    //Move and then set flag to FALSE.
    for(int i = 0; i < X_SIZE; i++)
    {
        for(int j = 0; j < Y_SIZE; j++)
        {
            if(grid[i][j] != NULL)
            {
                //cout << "calling grid[i][j]->Move()" << endl;
                grid[i][j]->Move();
            }
        }
    }

    //cout << endl << "after for loop." << endl;
    Breed();
    Die();

    SnapShot();
}

void Grid::Breed()
{
    for(int i = 0; i < X_SIZE; i++)
    {
        for(int j = 0; j < Y_SIZE; j++)
        {
            if(grid[i][j] != NULL)
            {
                //cout << "calling grid[i][j]->Breed()" << endl;
                grid[i][j]->Breed();
            }
        }
    }
}

void Grid::Die()
{
    for(int i = 0; i < X_SIZE; i++)
    {
        for(int j = 0; j < Y_SIZE; j++)
        {
            if(grid[i][j] != NULL)
            {
                grid[i][j]->Die();
            }
        }
    }
}

char** Grid::GetBoard()
{
    return snapShot;
}

//Generates Prey at random places.
void Grid::PlacePrey()
{
    Random r1, r2;

    int rand1 = r1.GenRand(X_SIZE);
    int rand2 = r2.GenRand(Y_SIZE);
    Coords newCoord(rand1, rand2);

    if(grid[newCoord.y][newCoord.x] == NULL)
    {
         grid[newCoord.y][newCoord.x] = new Prey(newCoord, grid);
    }
}

//Generates Predator at random places.
void Grid::PlacePred()
{
    Random r1, r2;

    int rand1 = r1.GenRand(X_SIZE);
    int rand2 = r2.GenRand(Y_SIZE);
    Coords newCoord(rand1, rand2);

    if(grid[newCoord.y][newCoord.x] == NULL)
    {
         grid[newCoord.y][newCoord.x] = new Predator(newCoord, grid);
    }
}

//Generates bomber at random places.
void Grid::PlaceBomb()
{
    Random r1, r2;

    int rand1 = r1.GenRand(X_SIZE);
    int rand2 = r2.GenRand(Y_SIZE);
    Coords newCoord(rand1, rand2);

    if(grid[newCoord.y][newCoord.x] == NULL)
    {
         grid[newCoord.y][newCoord.x] = new Bomber(newCoord, grid);
    }
}

//Generates God at random places.
void Grid::PlaceGod()
{
    int xMid, yMid;

    xMid = X_SIZE/2;
    yMid = Y_SIZE/2;

    Coords c(xMid, yMid);

    grid[c.y][c.x] = new God(c, grid);

}

//Initial creatures on the board
void Grid::InitCreat()
{
    PlaceGod();

    for(int i = 0; i < PREYNUM; i++)
    {
        PlacePrey();
    }

    for(int i = 0; i < PREDNUM; i++)
    {
        PlacePred();
    }

    for(int i = 0; i < BOMBNUM; i++)
    {
        PlaceBomb();
    }
}
