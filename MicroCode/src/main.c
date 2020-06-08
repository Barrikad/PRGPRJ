#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "ansi.h"
#include "arithmatic.h"
#include "project_utilities.h"
#include "apps.h"

int main(void)
{
    uart_init(128000);
    clrscr();
    startBall();
    while(1){}
}
