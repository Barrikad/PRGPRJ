#ifndef JOYSTICK_H_INCLUDED
#define JOYSTICK_H_INCLUDED
#include "pins.h"

//Pins, ports, and rcc for the different joystick positions
const gpio_pin_t JOYSTICK_UP;
const gpio_pin_t JOYSTICK_DOWN;
const gpio_pin_t JOYSTICK_LEFT;
const gpio_pin_t JOYSTICK_RIGHT;
const gpio_pin_t JOYSTICK_MIDDLE;


//Initializes the joystick, must be run before using joystick
//  Side effects: processor changes its configuration, when we change pin registers
void initJoystick();

//Returns 1 if joystick direction is pressed, 0 otherwise
//See the possible directions at the top of this file
uint8_t readJoystick(const gpio_pin_t gpio_pin);

#endif /* JOYSTICK_H_INCLUDED */
