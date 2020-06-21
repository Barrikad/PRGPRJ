#include <stdint.h>
#include "joystick.h"
#include "movement.h"

action_t movementFromJoystick(){
    uint16_t moves = 0;
    moves += readJoystick(JOYSTICK_MIDDLE) << 0;
    moves += readJoystick(JOYSTICK_LEFT) << 1;
    moves += readJoystick(JOYSTICK_RIGHT) << 2;
    moves += readJoystick(JOYSTICK_UP) << 3;
    moves += readJoystick(JOYSTICK_DOWN) << 4;
    return moves;
}
