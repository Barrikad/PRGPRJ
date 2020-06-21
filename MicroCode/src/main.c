#include <stdio.h>
#include <stdint.h>
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h"
#include "stm32f30x.h"
#include "player.h"
#include "entity_representation.h"
#include "fix_point_math.h"
#include "game.h"
#include "joystick.h"
#include "ansi.h"
#include "led.h"
#include "lcd.h"
#include "menu.h"
#include "level.h"
#include "boss_mode.h"
#include "movement.h"
#include "frame_timer.h"


int main(void) {
    // Note: In the final game, we want to start the state in mainMenu
    // Or even make a fancy intro-screen?

    // Test stuff below

    uart_init(115200);

    initJoystickForGame();

    initLevel(firstLevel);

    //initialize timer
    initFrameTimer();

    printf("test");

    cursorHide();
    while (1) {
        if (getFlag()) {
            unsetFlag();
            processGameTick();
        }
    }

}
