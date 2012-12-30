#ifdef RANDOM_H




#include "random.h"


int RandomInt(int from, int to)
{
    return rand()%(abs(to - from)) + from;
}

double RandomDouble(double from, double to)
{
    double f = (double)rand() / RAND_MAX;
    return from + f * (to - from);
}

#endif // RANDOM_H
