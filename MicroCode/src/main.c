#include <stdio.h>
#include <stdint.h>
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h"
#include "stm32f30x.h"
#include "player.h"
#include "entity_representation.h"
#include "fix_point_math.h"
#include "game_state.h"
#include "joystick.h"
#include "ansi.h"
#include "led.h"
#include "lcd.h"
#include "menu.h"
#include "level.h"
#include "boss_mode.h"
#include "draw_game.h"
#include "movement.h"
#include "actions.h"

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
            renderLevel();
            processInputLevel();
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
            renderScoreMenu(currentLevel);
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

    deg512_t rot = 0;
    vector_t pos = {4,4};
    vector_t hb = {1,1};
    placement_t plc= {pos,hb,rot};
    vector_t vel = {1,1};
    player_t player = {plc,vel,0,0,0};

    addPlayer(&player);
    initJoystickForGame();
    addPlayerWithInput(&player,movementFromJoystick);

    printf("test");

    while (1) {
        for(uint16_t i = 1; i > 0; i++){}
        processPlayerActionsInGame();
        movePlayers();
        moveBullets();
        clrscr();
        cursorToXY(40,0);
        printf("%i ",player.placement.rotation);

        //MUST BE MOVED FAST AS POSSIBLE
        if(shootflag){

            //make the placement of the bullet the same as the players, but with bullet hitbox
            vector_t position = player.placement.position;
            vector_t radiusHV = BULLET_RADIUS;
            deg512_t rotation = player.placement.rotation;
            placement_t bulletPlacement = {position,radiusHV,rotation};


            //set velocity to 1 in the direction the bullet is pointing
            vector_t bulletVelocity = {1 << 14,0};
            rotateVector(&bulletVelocity,player.placement.rotation);

            //create bullet specified above
            bullet_t bullet = {bulletPlacement,bulletVelocity};

            //move the bullet out of the player
            moveBullet(&bullet);

            addBullet(&bullet);

            shootflag = 0;
        }

        if(numberOfBullets() > 0){
            bullet_t b = *(*allBullets());
            printFix(b.placement.position.x);
            printf(" ");
            printFix(b.placement.position.y);
        }


        drawGame();
    }
}
