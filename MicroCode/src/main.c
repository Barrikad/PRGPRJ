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

typedef enum {
    game      = 0,
    mainMenu  = 1,
    helpMenu  = 2,
    scoreMenu = 3,
    miniGame  = 4,
    // TODO: Should this be here, or should it be special, triggered by a high priority interrupt, just to show our determination? YES!
    bossMode  = 5
} gamestate_t;

void mainGame() {
    // Note: In the final game, we want to start the state in mainMenu
    // Or even make a fancy intro-screen?
    gamestate_t currentGamestate = game;
    level_t currentLevel = firstLevel;

    uart_init(115200);
    // TODO: Initialize other stuff

    while(1) {
        if (currentGamestate == game) {
            // TODO: This
            // TODO: Add shouldShowBossKey
            // processEnemy();
            // moveEntities();
            // detectCollisions(&player, &entities);
            // if (player.health < 0) {
            //     // Show highscore
            //     currentGamestate = scoreMenu;
            // } else if (enemyCount == 0) {
            //     currentLevel = secondLevel;
            //     enterLevel(currentLevel);
            // }
            if (isBossKeyPressed()) {
                currentGamestate = bossMode;
            }
        } else if (currentGamestate == mainMenu) {
            renderMainMenu();
            // Change current menu
            switch (processInputMainMenu()) {
            case 1:
                // Start game
                currentGamestate = game;
                currentLevel = firstLevel;
                enterLevel(currentLevel);
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
            //renderScoreMenu(currentLevel);
            if (processInputScoreMenu()) {
                currentGamestate = mainMenu;
            }
        } else if (currentGamestate == miniGame) {
            // TODO
        } else if (currentGamestate == bossMode) {
            renderBossMode();
            if (processInputBossMode()) {
                // Return to game
                currentGamestate = game;
            }
        }
    }
}

int main(void) {
    // Run the actual game
    // mainGame();

    // Test stuff below

    uart_init(115200);

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

    initJoystickForGame();

    initLevel(firstLevel);

    //initialize timer
    initFrameTimer();

    //test enemy behavior. Will remove soon
    vector_t pos = {2 << 14,1 << 14};
    deg512_t rot = 0;
    placement_t plc = {pos, 1 << 13, 1 << 13, rot};
    vector_t cp1 = {2 << 14, 1 << 14};
    vector_t cp2 = {6 << 14, 1 << 14};
    vector_t cps[8] = {cp1,cp2,cp1,cp2,cp1,cp2,cp1,cp2};
    enemy_t enemy = {plc,0,0,0,cps,0};
    addEnemy(enemy);
    //tset

    printf("test");

    cursorHide();
    while (1) {
        if(getFlag()){
            processGameTick();
            unsetFlag();
        }
    }
}
