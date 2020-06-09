#include "stm32f30x_rcc.h"
#include <stdio.h>

#ifndef HARDWARE_IO_H_
#define HARDWARE_IO_H_

void setupHardwareIO();
uint8_t readJoystick();
void printJoystick(uint8_t joystick);

#endif /* HARDWARE_IO_H_ */
