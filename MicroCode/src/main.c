#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "ansi.h"
#include "arithmatic.h"
#include "project_utilities.h"

int main(void)
{
    uart_init(9600);
    int16_t tests[] = {0,45,-78,649};
    printf("\ndeg; sin; cos");
    for(int i = 0; i < 4; i++){
        int16_t conv = 512*tests[i]/360;
        printf("\n%i; ",tests[i]);
        printFix(expand(sin512(conv)));
        printf("; ");
        printFix(expand(cos512(conv)));
    }
    while(1){}
}
