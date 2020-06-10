#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "ansi.h"
#include "arithmatic.h"
#include "project_utilities.h"
#include "hardwareIO.h"
#include "timer2.h"
#include "stopwatch.h"


int main(void)
{
    uart_init(115200);
    clrscr();
    initTimer2(PRESCALER_SW,RELOAD_SW,increaseCenti);
    uint8_t second = curSecond();
    uint8_t pSecond = second;

    while(1) {
        second = curSecond();
        if(second != pSecond){
            printTime();
            pSecond = second;
        }
    }
}
