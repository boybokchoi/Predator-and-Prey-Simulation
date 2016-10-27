#ifndef DISPLAY_H
#define DISPLAY_H

#include "grid.h"
#include "gConst.h"

class Display
{
public:
    Display(char** b);

    void Show();

private:
    char** board;

};

#endif // DISPLAY_H
