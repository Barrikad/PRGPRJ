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
    // TODO: Make a fancy intro-screen?
    level_t currentLevel = invalidLevel;
    level_t nextLevel = invalidLevel;

    // Initialize the UART as the display during game.
    uart_init(115200);
    // Initialize the LCD for the menu and score/lives during game.
    lcdInit();
    // Initialize joystick both for the game and the menu.
    initJoystick();
    // Initialize the main menu.
    initMainMenu();

    // The main game loop.
    // We will always return to this, instead of having loops inside functions, since that makes our state explicit.
    while (1) {
        // Menu is currently open, game is not running.
        if (currentLevel == invalidLevel) {
            if (mainMenuFunction()) {
                currentLevel = firstLevel;
                initLevel(currentLevel);
            }
            helpMenuFunction();
            scoreMenuFunction();
            creditsMenuFunction();
        // Game is running.
        } else {
            // Render on a clock,
            if (getFrameFlag()) {
                unsetFrameFlag();
                // Debug print frame skips
                // Each time this number rises, a frame was skipped, and the game is running too slowly!
                cursorToXY(50, 0);
                printf("%5ld", getFramesSkipped());
                nextLevel = processGameTick(currentLevel);
                if (nextLevel == invalidLevel) {
                    currentLevel = nextLevel;
                    // TODO: Enter score menu
                    initMainMenu();
                } else if (nextLevel != currentLevel) {
                    currentLevel = nextLevel;
                    initLevel(currentLevel);
                }
            }
        }
    }
}
