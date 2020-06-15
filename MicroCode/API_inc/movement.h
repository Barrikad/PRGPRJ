#ifndef MOVEMENT_H_INCLUDED
#define MOVEMENT_H_INCLUDED
//Standard size for all encoded actions is uint16

//Translates the joystick position into encoded movement actions
//The following table describes the meaning of the separate bits being on (an example)
//  bit# | action
//    1  | shoot
//    2  | rotate left
//    3  | rotate right
//    4  | move forward
//    5  | move backward
uint16_t movementFromJoystick();

//Translates the joystick position into encoded selection actions for the menu
uint16_t selectionFromJoystick();

#endif /* MOVEMENT_H_INCLUDED */
