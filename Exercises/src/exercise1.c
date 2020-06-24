#include <stdint.h>
#include <stdio.h>
#include "arithmatic.h"

void exercise1(){
    int16_t a;
    printf("\n\n x x^2 x^3 x^4\n");
    for (a = 0; a < 10; a++) {
        printf("%8d%8d%8d%8d\n",a, power(a, 2), power(a, 3), power(a, 4));
    }
}

