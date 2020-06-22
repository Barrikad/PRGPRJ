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


void mainGame() {
    // Note: In the final game, we want to start the state in mainMenu
    // Or even make a fancy intro-screen?

    level_t currentLevel = firstLevel;

    uart_init(115200);
    // TODO: Initialize other stuff

    while(1) {
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
        }

    }
}

int main(void) {
    // Run the actual game
    // mainGame();

    // Test stuff below

    uart_init(115200);


    lcdInit();
    initJoystick();
    initMainMenu();

    initLevel(firstLevel);

    //initialize timer
    initFrameTimer();

    //test enemy behavior. Will remove soon
    vector_t pos = {5,0};
    deg512_t rot = 0;
    placement_t plc = {pos, 1 << 13, 1 << 13, rot};
    enemy_t enemy = {plc,0,0,0};
    addEnemy(enemy);
    //tset

    printf("test");

    cursorHide();

    uint8_t isGame = 0;

    while (1) {
        if (isGame) {
            if (getFlag()) {
                processGameTick();

                unsetFlag();
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
