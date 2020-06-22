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
#include "player_stat_graphics.h"


int main(void) {
    // Note: In the final game, we want to start the state in mainMenu
    // Or even make a fancy intro-screen?

    // Test stuff below

    uart_init(115200);


    lcdInit();
    initMainMenu();

    // Initialize joystick both for the game and the menu
    initJoystick();

    initLevel(firstLevel);

    //initialize timer
    initFrameTimer();

    printf("test");

    cursorHide();

    uint8_t isGame = 0;

    while (1) {
        if (isGame) {
            if (getFlag()) {
                unsetFlag();
                processGameTick();
            }

        }
        else {
            if (mainMenuFunction()) {
                isGame = 1;
            }
            helpMenuFunction();
            scoreMenuFunction();
            creditsMenuFunction();

        }
    }
}
