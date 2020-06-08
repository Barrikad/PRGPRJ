#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "ansi.h"
#include "arithmatic.h"
#include "project_utilities.h"
#define FIX14_SHIFT 14
#define FIX14_MULT(a, b) ( (a)*(b) >> FIX14_SHIFT )
#define FIX14_DIV(a, b) ( ((a) << FIX14_SHIFT) / b )

void printLine(vector_t vec, int16_t deg){
    printf("\n");
    printFix(expand(vec.x));
    printf(",");
    printFix(expand(vec.y));
    printf("; %i; ",deg);
    rotateVector(&vec,512*deg/360);
    printFix(expand(vec.x));
    printf(",");
    printFix(expand(vec.y));
}

int main(void)
{
    uart_init(9600);
    printf("\nvecIN; degs; vecOUT");
    vector_t v1 = {1 << FIX14_SHIFT,2 << FIX14_SHIFT};
    vector_t v2 = {6 << FIX14_SHIFT,4 << FIX14_SHIFT};
    vector_t v3 = {(-4) << FIX14_SHIFT,(-4) << FIX14_SHIFT};
    vector_t v4 = {(-4) << FIX14_SHIFT,2 << FIX14_SHIFT};

    printLine(v1,180);
    printLine(v2,-10);
    printLine(v3,900);
    printLine(v4,-35);

    while(1){}
}
