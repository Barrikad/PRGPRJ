#include <stdio.h>
#include <stdint.h>
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h"
#include "stm32f30x.h"
#include "joystick.h"
#include "ansi.h"


int main(void)
{
    uart_init(115200);
    clrscr();
    initJoystick();
    while(1){
        for(uint16_t i = 1; i > 0 ; i++){}

        if(readJoystick(JOYSTICK_DOWN))
            down(1);
        if(readJoystick(JOYSTICK_LEFT))
            left(1);
        if(readJoystick(JOYSTICK_RIGHT))
            right(1);
        if(readJoystick(JOYSTICK_UP))
            up(1);
        if(readJoystick(JOYSTICK_MIDDLE)){
            printf("X");
            left(1);
        }
    }
}
