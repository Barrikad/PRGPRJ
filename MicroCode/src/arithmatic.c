#include "arithmatic.h"

int16_t sin512(int16_t degs){
    return SIN[((degs % 512) + 512) % 512];
    //first % to get value within range
    //+ to make negatives positive
    //second % to reduce positives moved out of range with +
}

int16_t cos512(int16_t degs){
    return sin512(degs + 128);
}

int16_t power(int16_t a, int16_t exp) {
    // calculates a^exp
    int16_t i, r = 1;
    for (i = 1; i <= exp; i++)
        r *= a;
    return(r);
}
