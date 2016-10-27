#ifndef GRID_H
#define GRID_H

#include "gConst.h"
#include "coords.h"

class Grid
{
public:
    //Constructor
    Grid();
    Grid(Coords c);
    ~Grid();

    void Move();            //moves all creatures
    void Breed();           //creates a new creature of the same type
    void Die();             //kills off starved predators

    char GetFace(Coords c);
    void SnapShot();        //takes an image of the grid
    void PlacePrey();       //places prey into the grid
    void PlacePred();       //places predator into the grid
    void PlaceBomb();       //places bomb into the grid
    void PlaceGod();        //places 1 God into the grid
    void InitCreat();       //creates initial amount of each creature
    char** GetBoard();      //returns snapShot

    friend class Creature;
    int total;                      //total # of creatures

    Creature*** grid;       //pointer to the grid
    char** snapShot;        //pointer to the "faces" of the grid
};

#endif // GRID_H
