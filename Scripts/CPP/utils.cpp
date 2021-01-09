#include <tgmath.h>

double remainderEuclidianDivisionStrict(double dividend, double divisor)
{
    while(dividend > divisor)
        dividend -= divisor;
    return dividend;
}