#include "Random.h"
#include <stdlib.h>
#include <time.h>
using namespace std;

void initializeRandom()
{
    srand(time(NULL));
}

unsigned int randInt(unsigned int upperBound)
{
    return rand() % upperBound;
}

double randDouble(double dMin, double dMax)
{
    double d = (double)rand() / RAND_MAX;
    return dMin + d * (dMax - dMin);
}
