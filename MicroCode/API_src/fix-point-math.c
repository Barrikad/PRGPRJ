#include <stdint.h>
#include "lut.h"
#include "fix_point_math.h"

// Calculates sine of an angle, with 512 degrees in a circle
int16_t sine(mytype degs){
    //"x & (y - 1)" is the same as "x mod y", if y is a power of two
    //also enforcing the result to be larger than 0
    return SIN[degs & 511];
}

// Calculates cosine of an angle, with 512 degrees in a circle
int16_t cosine(int16_t degs){
    //we use the property that cos(x) = sin(x+90) (in ordinary degrees)
    return sin512(degs + 128); //512*90/360 = 128
}

// Rotates the vector at the pointer the given number of degrees, with 512 degs in a circle
void rotateVector(vector_t *v, int16_t degs){
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
