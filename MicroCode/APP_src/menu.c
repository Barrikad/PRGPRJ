#include <stdio.h>
#include <string.h>
#include "lcd.h"
#include "joystick.h"
#include "player.h"
#include "game.h"
#include "menu.h"
#include "falling_edge_selection.h"

typedef enum {
    newGame    = 0,
    help  = 1,
    score  = 2,
    credits = 3
} selectedOption_t;

static menustate_t currentGamestate = mainMenu;
static selectedOption_t currentSelectedOption = newGame;


static void renderMainMenu() {
    char* newGame[] = {"New Game     ->Select", "Help         <-Back", "Highscore", "Credits"};
    lcdClear();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < strlen(newGame[i]); j++) {
            lcdWriteChar(newGame[i][j], j * 6, i * 8);
        }
    }
    lcdFlush();
}

uint8_t processInputMainMenu() {
    if (hasPressedRight()) {
        return 1;
    }
    if (hasPressedDown()) {
        return 2;
    }
    if (hasPressedUp()) {
        return 3;
    }
    return 0;
}

static void renderHelpMenu() {
    // TODO: This!
    char* helpMenuText[] = {"Control the tank with", "the joystick.", "Shoot by pressing the", "joystick down."};
    lcdClear();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < strlen(helpMenuText[i]); j++) {
            lcdWriteChar(helpMenuText[i][j], j * 6, i * 8);
        }
    }
    lcdFlush();
}

uint8_t processInputHelpMenu() {
    if (hasPressedLeft()) {
        return 1;
    }
    return 0; // Stays in submenu
}

static void scoreFormatting(char score[3][14], player_t* players, uint8_t numPlayers){
    for (int i = 0; i < numPlayers; i++) {
        sprintf(score[i], "%13d",players[i].points);
    }
}

static void renderScoreMenu(uint8_t clearedLevels, player_t* players, uint8_t numPlayers) {
    char* highscore = "      Highscore      ";
    char* playerNumber[] = {"Player 1", "Player 2", "Player 3"}; // if more than 3 players is wanted then a scroll function is needed
    char score[3][14];
    scoreFormatting(score, players, numPlayers);

    lcdClear();

    for (int i = 0; i < strlen(highscore); i++) {
        lcdAntiWriteChar(highscore[i], i * 6, 0);
    }

    for (int i = 1; i < 4; i++) {
        for (int j = 0; j < strlen(playerNumber[i]); j++) {
            lcdWriteChar(playerNumber[i][j], j * 6, i * 8);
        }
    }

     for (int i = 1; i < 4; i++) {
        for (int j = 8; j < 21; j++) {
                lcdWriteChar(score[i][j], j * 6, i * 8);
        }
    }

    lcdFlush();
}

uint8_t processInputScoreMenu() {
    if (hasPressedLeft()) {
        return 1;
    }
    return 0; // Stays in submenu
}

static void renderCreditsMenu() {
    char* credits[] = {"Created by:","Mads Marquart", "Simon Tobias Lund", "Gustav Leth-Espensen"};
    lcdClear();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < strlen(credits[i]); j++) {
            lcdWriteChar(credits[i][j], j * 6, i * 8);
        }
    }
    lcdFlush();
}

uint8_t processInputCreditsMenu() {
    if (hasPressedLeft()) {
        return 1;
    }
    return 0;
}

static void menuOptionNewGame() {
    char* antiNewGame = {"New Game"};
    for (int j = 0; j < strlen(antiNewGame); j++) {
        lcdAntiWriteChar(antiNewGame[j], j * 6, 0);
    }
    lcdFlush();
}

static void menuOptionHelp() {
    char* antiHelp = {"Help"};
    for (int j = 0; j < strlen(antiHelp); j++) {
        lcdAntiWriteChar(antiHelp[j], j * 6, 8);
    }
    lcdFlush();
}

static void menuOptionHighscore() {
    char* antiHighscore = {"Highscore"};
    for (int j = 0; j < strlen(antiHighscore); j++) {
        lcdAntiWriteChar(antiHighscore[j], j * 6, 16);
    }
    lcdFlush();
}

static void menuOptionCredits() {
    char* antiCredits = {"Credits"};
    for (int j = 0; j < strlen(antiCredits); j++) {
        lcdAntiWriteChar(antiCredits[j], j * 6, 24);
    }
    lcdFlush();
}


void initMainMenu() {
    renderMainMenu();
    menuOptionNewGame();
}


void mainMenuFunction() {
    if (currentGamestate == mainMenu) {
        if (currentSelectedOption == newGame) {
            uint8_t joystickInput = processInputMainMenu();
            if (joystickInput == 1) {
                currentGamestate = game;
            }
            else if (joystickInput == 2) {
                currentSelectedOption = help;
                renderMainMenu();
                menuOptionHelp();
            }
            else if (joystickInput == 3) {
                currentSelectedOption = credits;
                renderMainMenu();
                menuOptionCredits();
            }
        }
        else if (currentSelectedOption == help) {
            uint8_t joystickInput = processInputMainMenu();
            if (joystickInput == 1) {
                currentGamestate = helpMenu;
            }
            else if (joystickInput == 2) {
                currentSelectedOption = score;
                renderMainMenu();
                menuOptionHighscore();
            }
            else if (joystickInput == 3) {
                currentSelectedOption = newGame;
                renderMainMenu();
                menuOptionNewGame();
            }
        }
        else if (currentSelectedOption == score) {
            uint8_t joystickInput = processInputMainMenu();
            if (joystickInput == 1) {
                currentGamestate = scoreMenu;
            }
            else if (joystickInput == 2) {
                currentSelectedOption = credits;
                renderMainMenu();
                menuOptionCredits();
            }
            else if (joystickInput == 3) {
                currentSelectedOption = help;
                renderMainMenu();
                menuOptionHelp();
            }
        }
        else if (currentSelectedOption == credits) {
            uint8_t joystickInput = processInputMainMenu();
            if (joystickInput == 1) {
                currentGamestate = creditsMenu;
            }
            else if (joystickInput == 2) {
                currentSelectedOption = newGame;
                renderMainMenu();
                menuOptionNewGame();
            }
            else if (joystickInput == 3) {
                currentSelectedOption = score;
                renderMainMenu();
                menuOptionHighscore();
            }
        }
    }
}

/*
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
*/

void helpMenuFunction() {
    if (currentGamestate == helpMenu) {
        renderHelpMenu();
        uint8_t joystickInput = processInputHelpMenu();
        if (joystickInput == 1) {
            currentGamestate = mainMenu;
            renderMainMenu();
            menuOptionHelp();
        }
     }
}

void scoreMenuFunction() {
    if (currentGamestate == scoreMenu) {
        //renderScoreMenu();
        uint8_t joystickInput = processInputScoreMenu();
        if (joystickInput == 1) {
            currentGamestate = mainMenu;
            renderMainMenu();
            menuOptionHighscore();
        }
    }
}

void creditsMenuFunction() {
    if (currentGamestate == creditsMenu) {
        renderCreditsMenu();
        uint8_t joystickInput = processInputCreditsMenu();
        if (joystickInput == 1) {
            currentGamestate = mainMenu;
            renderMainMenu();
            menuOptionCredits();
        }
    }
}




/*

// Sudocode/ Idea for main menu
printf("Main menu")

printf("\n\nNew game");
printf("\nHelp");
printf("\nHighscore");
printf("\nCredtis");

uint8_t menustate = 1;

if (menustate = 1){

    if (JOYSTICK_MIDDLE) {
        menustate = 0;
    }
    if (JOYSTICK_DOWN) {
        menustate = 2;
    }
}

if (menustate = 2) {
    if (JOYSTICK_MIDDLE) {
        menustate = 21;
        while(menustate == 21)
        printf("Move your tank with the joystick");
        printf("\nx to shoot");
        printf("\nb for bosskey");
        printf("\n\nMove joystick left for main menu")

        if (JOYSTICK_LEFT) {
            menustate = 2;
        }
    }

    if (JOYSTICK_DOWN) {
        menustate = 3;
    }
    if (JOYSTICK_UP) {
        menustate = 1;
    }

}

if (menustate = 3) {
    if (JOYSTICK_MIDDLE) {
        menustate = 31;
        while (menustate == 31){
            printf("Highscore")
            printf("1.: %d", highscore);
            printf("2.: %d", highscore);
            printf("3.: %d", highscore);

        if (JOYSTICK_LEFT) {
            menustate = 3;
        }
        }
    }
    if (JOYSTICK_DOWN) {
        menustate = 4;
    }
    if (JOYSTICK_UP) {
        menustate = 2;
    }
}

if (menustate = 4) {
    if (JOYSTICK_MIDDLE) {
        menustate = 41;
        while(menustate == 41) {}
            printf("Mads Tolstrup Marquart ");
            printf("\nSimon Tobias Lund");
            printf("\nGustav Leth-Espensen");
            printf("\n DTU SPACE course 30010")

        if (JOYSTICK_LEFT) {
            menustate = 4;
        }
    }
    if (JOYSTICK_DOWN) {
        menustate = 1;
    }
    if (JOYSTICK_UP) {
    menustate = 3;
    }
}

*/


