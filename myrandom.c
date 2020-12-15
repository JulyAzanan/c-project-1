#include <stdio.h>
#include <stdlib.h>
#include "myrandom.h"

/**
*Requires : min < max <= RAND_MAX
*Assigns : nothing
*Ensures : returns a pseudo-random value between min and max both included.
*/
int rand_between(int min, int max) {
    double r = (double)rand()/(double)RAND_MAX;
    return (int)((r * (max - min + 1)) + min);
}
