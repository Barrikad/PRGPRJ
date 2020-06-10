#include <stdio.h>
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "ansi.h"
#include "arithmatic.h"
#include "project_utilities.h"
#include "hardwareIO.h"
#include "terminalInput.h"
#include "timer.h"
#include "display.h"


int main(void)
{
    uart_init(115200);

    lcd_init();
    initDisplay();
    initTimer2(63999,9,setFlag);
    enableTimer2();

    lcdWriteString("hello world", 0, 1);

    while(1){
        lcdUpdate();
    }
}
