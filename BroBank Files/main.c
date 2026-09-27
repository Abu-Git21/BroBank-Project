#include <stdio.h>
#include "josephus.h"

int main(void) {
    int eliminated[CAPACITY], count = 0;

    int survivor = josephusSurvivor(7, 3, eliminated, &count);

    printf("Exercise 10 starter\nJosephus survivor: %d (complete TODOs for full output)\n",
           survivor);

    return 0;
}