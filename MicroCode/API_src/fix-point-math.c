#include <stdint.h>
#include "lut.h"
#include "fix_point_math.h"

//shift position of the radix point to the left by two
fix16_t expand(fix14_t x){
    //if the number is positive this is trivial
    if(x > 0){
        return x << 2;
    }
    //if the number is negative it must be converted to positive and then back
    else{
        x *= -1;
        x = x << 2;
        x *= -1;
        return x;
    }
}
//shift position of the radix point to the right by two
fix14_t reduce(fix16_t x){
    //if the number is positive this is trivial
    if(x > 0){
        return x >> 2;
    }
    //if the number is negative it must be converted to positive and then back
    else{
        x *= -1;
        x = x >> 2;
        x *= -1;
        return x;
    }
}

// Calculates sine of an angle, with 512 degrees in a circle
fix14_t sine(deg512_t degs){
    //"x & (y - 1)" is the same as "x mod y", if y is a power of two
    //also enforcing the result to be larger than 0
    return SIN[degs & 511];
}

// Calculates cosine of an angle, with 512 degrees in a circle
fix14_t cosine(deg512_t degs){
    //we use the property that cos(x) = sin(x+90) (in ordinary degrees)
    return sin512(degs + 128); //  512*90/360 = 128
}

// Rotates the vector at the pointer the given number of degrees, with 512 degs in a circle
void rotateVector(vector_t *v, deg512_t degs){
    // Temp variables
    int32_t x = (*v).x;
    int32_t y = (*v).y;

    // Get the sin and cos of the angle
    int32_t cosT = cos512(degs);
    int32_t sinT = sin512(degs);

    // Use the formula for rotating a vector
    (*v).x = FIX14_MULT(x,cosT) - FIX14_MULT(y,sinT);
    (*v).y = FIX14_MULT(x,sinT) + FIX14_MULT(y,cosT);
}
