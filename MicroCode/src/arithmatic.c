#include "arithmatic.h"

int16_t sin512(int16_t degs){
    return SIN[degs & 511];
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

void rotateVector(vector_t *v, int16_t degs){
    int32_t x = (*v).x;
    int32_t y = (*v).y;
    int32_t cosT = cos512(degs);
    int32_t sinT = sin512(degs);
    (*v).x = FIX14_MULT(x,cosT) - FIX14_MULT(y,sinT);
    (*v).y = FIX14_MULT(x,sinT) + FIX14_MULT(y,cosT);
}
