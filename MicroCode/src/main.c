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
    initOutput(4,'B');
    initJoystick();

    while(1) {
        uint8_t js = readJoystick();
        if(js & 1){
            setOutput(4,'B',1);
        }
        if(js & 2){
            setOutput(4,'B',0);
        }
    }
}
