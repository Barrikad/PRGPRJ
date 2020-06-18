#include "sin_lut.h"
#include "asin_lut.h"
#include "fix_point_math.h"

//Note on all math functions:
//shift operation is according to documentation not defined for negative numbers,
//so operations requiring it must be switched to positive and then back to negative

//shift position of the radix point to the left by two
fix16_t expand(fix14_t x){
    //if the number is positive this is trivial
    if(x >= 0){
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
    if(x >= 0){
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
    return sine(degs + 128); //  512*90/360 = 128
}

deg512_t asine(fix14_t s){
    if(s < 0){
        //convert to fix8
        s >>= 6;
        //set 9th bit to make negativ
        s |= 1 << 9;
        //only consider last 9 bits
        s &= 0x1FF;
    }
    else{
        //convert to fix8
        s >>= 6;
        //only consider last 8 bits
        s &= 0xFF;
    }
    return ASIN[s];
}

deg512_t acosine(fix14_t c){
    return 128 - asine(c);
}


//private function to round a guaranteed positive number
static int16_t roundPositive(fix14_t x){
    //remove all decimals except the most significant
    x = x >> 13;
    //round up if most significant decimal is 1
    x += x & 1;
    //remove most significant decimal
    return x >> 1;
}

int16_t roundFix(fix14_t x){
    if(x >= 0){
        return roundPositive(x);
    }
    else{
        //if number is negative, switch to positive, round, then switch back
        x *= -1;
        x = roundPositive(x);
        return -1*x;
    }
}

int16_t floorFix(fix14_t x){
    if(x >= 0){
        return x >> 14;
    }
    else{
        //if number is negative, switch to positive, floor, then switch back
        x *= -1;
        x = x >> 14;
        return -1*x;
    }
}

fix14_t createFix(int16_t x) {
    return x << FIX14_SHIFT;
}

fix14_t roundFixToFix(fix14_t x) {
    return x << FIX14_SHIFT;
}

// Rotates the vector at the pointer the given number of degrees, with 512 degs in a circle
void rotateVector(vector_t *v, deg512_t degs){
    // Temp variables
    int32_t x = (*v).x;
    int32_t y = (*v).y;

    // Get the sin and cos of the angle
    int32_t cosT = cosine(degs);
    int32_t sinT = sine(degs);

    // Use the formula for rotating a vector
    (*v).x = FIX14_MULT(x,cosT) - FIX14_MULT(y,sinT);
    (*v).y = FIX14_MULT(x,sinT) + FIX14_MULT(y,cosT);
}
