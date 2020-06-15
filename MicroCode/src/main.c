#include <stdio.h>
#include <stdint.h>
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h"
#include "stm32f30x.h"
#include "joystick.h"
#include "ansi.h"
#include "led.h"
#include "lcd.h"
#include "menu.h"

typedef enum uint8_t {
    game      = 0,
    mainMenu  = 1,
    helpMenu  = 2,
    scoreMenu = 3,
    miniGame  = 4,
    // TODO: Should this be here, or should it be special, triggered by a high priority interrupt, just to show our determination?
    bossKey   = 5
} gamestate_t;

// You can put test stuff in this function for now
void testInit() {
    initLeds();
    setLed(LED_RED);
    clearLed(LED_BLUE);
    setLed(LED_GREEN);

    lcdInit();
    lcdClear();
    lcdWriteChar('T', 0, 0);
    lcdWriteChar('e', 6, 0);
    lcdWriteChar('s', 12, 0);
    lcdWriteChar('t', 18, 0);
    lcdWriteChar(' ', 24, 0);
    lcdWriteChar('!', 24, 7);
    lcdWriteChar('!', 30, 15);
    lcdWriteChar('!', 36, 23);
    lcdWriteChar('!', 42, 31);
    lcdFlush();
}

// You can put test stuff in this function for now
void test() {
    printf("test");
}

int main(void) {
    // Note: In the final game, we want to start the state in mainMenu
    // Or even make a fancy intro-screen?
    gamestate_t currentGamestate = game;
    uint8_t currentLevel = 0;

    uart_init(115200);

    // Init other stuff
    testInit();

    while(1) {
        if (currentGamestate == game) {
            // TODO: This
            test();
        } else if (currentGamestate == mainMenu) {
            renderMainMenu();
            // Change current menu
            switch (processInputMainMenu()) {
            case 1:
                // Start game
                currentGamestate = game;
                currentLevel = 0;
                // initLevel(currentLevel);
            case 2:
                // Open help menu
                currentGamestate = helpMenu;
            case 3:
                // Open minigame
                currentGamestate = miniGame;
            default:
                // Do nothing
                break;
            }
        } else if (currentGamestate == helpMenu) {
            renderHelpMenu();
            if (processInputHelpMenu()) {
                currentGamestate = mainMenu;
            }
        } else if (currentGamestate == scoreMenu) {
            // TODO: Pass correct parameters
            renderScoreMenu(currentLevel);
            if (processInputScoreMenu()) {
                currentGamestate = mainMenu;
            }
        }
    }
}
