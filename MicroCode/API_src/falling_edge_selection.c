#include "joystick.h"
#include "falling_edge_selection.h"

static uint8_t lastJoystickLeft;
static uint8_t lastJoystickRight;
static uint8_t lastJoystickUp;
static uint8_t lastJoystickDown;

uint8_t hasPressedLeft() {
    uint8_t currentJoystickLeft = readJoystick(JOYSTICK_LEFT);
    if (lastJoystickLeft && !currentJoystickLeft) {
        lastJoystickLeft = currentJoystickLeft;
        return 1;  // Falling edge of JOYSTICK_LEFT
    }
    lastJoystickLeft = currentJoystickLeft;
    return 0;
}


uint8_t hasPressedRight() {
    uint8_t currentJoystickRight = readJoystick(JOYSTICK_RIGHT);
    if (lastJoystickRight && !currentJoystickRight) {
        lastJoystickRight = currentJoystickRight;
        return 1;  // Falling edge of JOYSTICK_LEFT
    }
    lastJoystickRight = currentJoystickRight;
    return 0;
}

uint8_t hasPressedUp() {
    uint8_t currentJoystickUp = readJoystick(JOYSTICK_UP);
    if (lastJoystickUp && !currentJoystickUp) {
        lastJoystickUp = currentJoystickUp;
        return 1;  // Falling edge of JOYSTICK_LEFT
    }
    lastJoystickUp = currentJoystickUp;
    return 0;
}


uint8_t hasPressedDown() {
    uint8_t currentJoystickDown = readJoystick(JOYSTICK_DOWN);
    if (lastJoystickDown && !currentJoystickDown) {
        lastJoystickDown = currentJoystickDown;
        return 1;  // Falling edge of JOYSTICK_LEFT
    }
    lastJoystickDown = currentJoystickDown;
    return 0;
}
