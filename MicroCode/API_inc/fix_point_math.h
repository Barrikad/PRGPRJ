#ifndef FIX_POINT_MATH_H_INCLUDED
#define FIX_POINT_MATH_H_INCLUDED

//Defines operations for multiplication and division with fix point numbers
#define FIX14_SHIFT 14
#define FIX14_MULT(a, b) ( (a)*(b) >> FIX14_SHIFT )
#define FIX14_DIV(a, b) ( ((a) << FIX14_SHIFT) / b )

// Vector/point structure
typedef struct {
    int32_t x, y;
} vector_t;

// Degrees expressed with 512 degrees in a circle
typedef uint8_t deg512_t;

// Fixed point number with 14 decimal places
typedef uint32_t fix14_t;

// Fixed point number with 16 decimal places
typedef uint32_t fix16_t;

// Functions for converting a number, x, between 14 and 16 decimal places
fix16_t extend(fix14_t x);
fix14_t reduce(fix)

// Sinus and cosine of an angle
fix14_t sin512(deg512_t degs);
fix14_t cos512(deg512_t degs);

// Rotates the given vector the given number of degrees
//    Side effects : the vector at the pointer location is changed
void rotateVector(vector_t *v, deg512_t degs);

#endif /* FIX_POINT_MATH_H_INCLUDED */
