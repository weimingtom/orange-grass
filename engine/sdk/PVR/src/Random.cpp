#include "Random.h"
#include <stdlib.h>

// global default random number generator
CTrivialRandomGenerator gRandom(12345);

// TODO: use something better than rand(), such as a twister or r250
void CTrivialRandomGenerator::setSeed(unsigned int seed)
{
    mSeed = seed;
}

// we use rand_r here to keep various instances independant
int CTrivialRandomGenerator::randI()
{
#ifdef WIN32
    int ret = rand();
#else
    int ret = rand_r(&mSeed);
#endif
    return ret;
}
