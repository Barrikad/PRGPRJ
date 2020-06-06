/*
**
**                           Main.c
**
**
**********************************************************************/
/*
   Last committed:     $Revision: 00 $
   Last changed by:    $Author: $
   Last changed date:  $Date:  $
   ID:                 $Id:  $

**********************************************************************/
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "ansi.h"
int16_t power(int16_t a, int16_t exp) {
    // calculates a^exp
    int16_t i, r = 1;
    for (i = 1; i <= exp; i++)
        r *= a;
    return(r);
}
int main(void)
{
    gotoxy(0,0);
    int16_t a;
    uart_init( 9600 ); // Initialize USB serial at 9600 baud
    printf("\n\n x x^2 x^3 x^4\n");
    for (a = 0; a < 10; a++) {
        printf("%8d%8d%8d%8d\n",a, power(a, 2), power(a, 3), power(a, 4));
    }
    window(22,27,28,33,"Yo",0);
    window(22,5,28,25,"Hello",1);
    while(1){}
}
