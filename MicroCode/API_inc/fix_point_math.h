#ifndef FIX_POINT_MATH_H_INCLUDED
#define FIX_POINT_MATH_H_INCLUDED
#include <stdint.h>

//Defines operations for multiplication and division with fix point numbers
#define FIX14_SHIFT 14
#define FIX14_MULT(a, b) ( (a)*(b) >> FIX14_SHIFT )
#define FIX14_DIV(a, b) ( ((a) << FIX14_SHIFT) / b )

// Degrees expressed with 512 degrees in a circle
typedef int16_t deg512_t;

// Fixed point number with 2 ... and 14 decimal places
typedef int16_t fix2_14_t;

// Fixed point number with 14 decimal places
typedef int32_t fix14_t;

// Fixed point number with 16 decimal places
typedef int32_t fix16_t;

// Vector/point structure
typedef struct {
    fix14_t x, y;
} vector_t;

// Functions for converting a number, x, between 14 and 16 decimal places
fix16_t expand(fix14_t x);
fix14_t reduce(fix16_t x);

// Sinus and cosine of an angle
// calculated with lut
fix14_t sine(deg512_t degs);
fix14_t cosine(deg512_t degs);

// Arcsine and arccosine of a fixpoint <1 and >-1
// calculated with lut
deg512_t asine(fix14_t s);
deg512_t acosine(fix14_t c);

// Square root of fix14 number
// Calculated with the babylonian method for 15 iterations
fix14_t squrt(fix14_t x);

int16_t roundFix(fix14_t x);
int16_t floorFix(fix14_t x);

// Create a 18.4 fixed point number from the given whole number.
fix14_t createFix(int16_t x);

// Round a fixed point number.
// TODO: Rename this!
fix14_t roundFixToFix(fix14_t x);

// Rotates the given vector the given number of degrees
//    Side effects : the vector at the pointer location is changed
void rotateVector(vector_t *v, deg512_t degs);

#endif /* FIX_POINT_MATH_H_INCLUDED */
