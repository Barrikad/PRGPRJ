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
    //TODO: too much indentation, should refactor
    //negative numbers must be treated differently
    if(s < 0){
        //cap at -1
        if(s < -(1 << 14)){
            s = 256;
        }
        else{
            //convert to fix8
            s >>= 6;
            //set 9th bit to make negative
            s |= 1 << 9;
            //only consider last 9 bits
            s &= 0x1FF;
        }
    }
    else{
        //cap at 1
        if(s >= 1 << 14){
            s = 255;
        }
        else{
            //convert to fix8
            s >>= 6;
            //only consider last 8 bits
            s &= 0xFF;
        }
    }
    return ASIN[s];
}

deg512_t acosine(fix14_t c){
    //acos(x) = pi/2 - asin(x)
    return 128 - asine(c);
}

fix14_t squrt(fix14_t x){
    uint8_t i;
    //  note: division of fixpoint by int is safe
    //initial estimate
    fix14_t estimate = x/3;

    //iterative estimates
    for(i = 0; i < 15; i++){
        estimate = (estimate + FIX14_DIV(x,estimate)) / 2;
    }

    return estimate;
}

fix14_t vectorLen(vector_t v){
    //signedness of x and y doesn't matter for distance
    //so we convert to positive first
    if(v.x < 0){
        v.x = -v.x;
    }
    if(v.y < 0){
        v.y = -v.y;
    }

    //convert to fix5
    v.x >>= 9;
    v.y >>= 9;

    //calculate x^2+y^2. multiplication converts back to fix10
    fix14_t x2y2 = (v.x * v.x) + (v.y * v.y);

    //return distance converted to fix14
    return squrt(x2y2 << 4);
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
        x = (~x) + 1;
        x = roundPositive(x);
        return ~(x - 1);
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

fix14_t absFix(fix14_t x){
    if(x < 0){
        x = -x;
    }
    return x;
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
