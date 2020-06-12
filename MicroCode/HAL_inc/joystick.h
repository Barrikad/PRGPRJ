#ifndef JOYSTICK_H_INCLUDED
#define JOYSTICK_H_INCLUDED

//Initializes the joystick, must be run before using joystick
void initJoystick();

//Returns a byte reflecting joystick position
//The different bits reflect different joystick positions
//If multiple bits are set, then the joystick is in a position between the bits
//
//  Bit# | Joystick position
//  1    | UP
//  2    | DOWN
//  3    | LEFT
//  4    | RIGHT
//  5    | MIDDLE (IN)
uint8_t readJoystick();

#endif /* JOYSTICK_H_INCLUDED */
