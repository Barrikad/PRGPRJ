#ifndef FALLING_EDGE_SELECTION_H_INCLUDED
#define FALLING_EDGE_SELECTION_H_INCLUDED

#include <stdint.h>

// Check if the joystick has been pressed left and returned to middle position.
uint8_t hasPressedLeft();
// Check if the joystick has been pressed right and returned to middle position.
uint8_t hasPressedRight();
// Check if the joystick has been pressed up and returned to middle position.
uint8_t hasPressedUp();
// Check if the joystick has been pressed down and returned to middle position.
uint8_t hasPressedDown();


#endif /* FALLING_EDGE_SELECTION_H_INCLUDED */
