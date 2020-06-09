#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "ansi.h"
#include "arithmatic.h"
#include "project_utilities.h"
#include "ball.h"
#include "hardware_io.h"

int main(void)
{
    uart_init(115200);
    clrscr();
//    startBall();
    setupHardwareIO();
	uint8_t previousJoystick = 0;
    while(1) {
    	uint8_t currentJoystick = readJoystick();
    	if (currentJoystick != previousJoystick) {
    		printJoystick(currentJoystick);
			previousJoystick = currentJoystick;
    	}
    }
}
