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

    initJoystickForGame();

    initLevel(firstLevel);

    //initialize timer
    initFrameTimer();

    printf("test");

    cursorHide();
    while (1) {
        if(getFlag()){
            processGameTick();
            unsetFlag();
        }
    }

}
