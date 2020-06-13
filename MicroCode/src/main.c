#include <stdio.h>
#include <stdint.h>
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h"
#include "stm32f30x.h"
#include "joystick.h"
#include "ansi.h"
#include "led.h"


int main(void)
{
    uart_init(115200);


    initLeds();

    /*
    setLed(LED_RED);
    setLed(LED_BLUE);
    setLed(LED_GREEN);
    */

    clearLed(LED_RED);
    clearLed(LED_BLUE);
    clearLed(LED_GREEN);


    while(1){

    }
}
