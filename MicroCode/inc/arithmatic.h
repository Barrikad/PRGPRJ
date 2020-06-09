#include <stdint.h>
#include <stdio.h>
#include "lut.h"

#ifndef ARITHM_H_INCLUDED
#define ARITHM_H_INCLUDED

#define FIX14_SHIFT 14
#define FIX14_MULT(a, b) ( (a)*(b) >> FIX14_SHIFT )
#define FIX14_DIV(a, b) ( ((a) << FIX14_SHIFT) / b )

typedef struct {
    int32_t x, y;
} vector_t;

int16_t sin512(int16_t degs);
int16_t cos512(int16_t degs);
int16_t power(int16_t a, int16_t exp);
void rotateVector(vector_t *v, int16_t degs);

#endif /* ARITHM_H_INCLUDED */

