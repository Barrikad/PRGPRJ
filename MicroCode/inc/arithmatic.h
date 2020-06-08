#include <stdint.h>
#include <stdio.h>
#include "lut.h"

#ifndef ARITHM_H_INCLUDED
#define ARITHM_H_INCLUDED

typedef struct {
    int32_t x, y;
} vector_t;

int16_t sin512(int16_t degs);
int16_t cos512(int16_t degs);
int16_t power(int16_t a, int16_t exp);
void rotateVector(vector_t *v, int16_t degs);

#endif /* ARITHM_H_INCLUDED */

