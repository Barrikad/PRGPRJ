#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "ansi.h"
#include "arithmatic.h"
#include "project_utilities.h"
#include "hardwareIO.h"

int main(void)
{
    uart_init(115200);
    clrscr();
    initJoystick();
    initLeds();

    while(1) {
        ledToJoystick();
    }
}
