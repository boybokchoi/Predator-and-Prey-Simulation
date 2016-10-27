#include "random.h"
#include <cstdlib>
#include <vector>

Random::Random()
{
    randNum = 0;
}

int Random::GenRand(int highestNum)
{

    if(highestNum == 0)
        return highestNum;
    else
    {
       randNum = rand()%highestNum;  //random number from 0 to HIGHESTNUM
       return randNum;
    }

}
