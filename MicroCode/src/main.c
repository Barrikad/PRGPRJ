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
#include "keyboard.h"
#include "movement.h"
#include "frame_timer.h"
#include "player_stat_graphics.h"
#include "led.h"


int main(void) {
    // TODO: Make a fancy intro-screen?
    uint8_t bossMode = 0;
    level_t currentLevel = invalidLevel;
    level_t nextLevel = invalidLevel;
    uint8_t shouldEnterGame = 0;

    // Initialize the UART as the display during game.
    uart_init(115200);

    clearKeys();
    // Initialize the LCD for the menu and score/lives during game.
    lcdInit();
    // Initialize LED for both game and menu
    initLeds();
    // Initialize joystick both for the game and the menu.
    initJoystick();
    // Initialize the main menu.
    initMainMenu();

    // The main game loop.
    // We will always return to this, instead of having loops inside functions, since that makes our state explicit.
    while (1) {
        if (bossMode) {
            // If should exit boss mode
            if (processBossMode()) {
                bossMode = 0;
                // Reset current level
                initLevel(currentLevel);
            }
        // Menu is currently open, game is not running.
        } else if (currentLevel == invalidLevel) {
            shouldEnterGame = processMenu();
            if (shouldEnterGame) {
                currentLevel = initialLevel;
                initLevel(currentLevel);
            }
        // Game is running.
        } else {
            // Check if boss has entered office. Nothing is more important!
            if (isBossKeyPressed()) {
                initBossMode();
                bossMode = 1;
            // Render on a clock,
            } else if (getFrameFlag()) {
                unsetFrameFlag();
                // Debug print frame skips
                // Each time this number rises, a frame was skipped, and the game is running too slowly!
                cursorToXY(50, 0);
                printf("%5ld", getFramesSkipped());
                nextLevel = processGameTick(currentLevel);
                if (nextLevel == invalidLevel) {
                    currentLevel = nextLevel;
                } else if (nextLevel != currentLevel) {
                    currentLevel = nextLevel;
                    initLevel(currentLevel);
                }
            }
        }
    }
}
