#include <stdio.h>
#include <string.h>
#include "lcd.h"
#include "player.h"
#include "game.h"
#include "menu.h"
#include "falling_edge_selection.h"
#include "player_stat_graphics.h"

typedef enum {
    newGame    = 0,
    help  = 1,
    score  = 2,
    credits = 3
} selectedOption_t;

static menustate_t currentGamestate = mainMenu;
static selectedOption_t currentSelectedOption = newGame;


static void renderMainMenu() {
    char* newGame[] = {"New Game     ->Select", "Help         <-Back", "Game Play Help", "Credits"};
    uint8_t i, j;
    lcdClear();
    for (i = 0; i < 4; i++) {
        for (j = 0; j < strlen(newGame[i]); j++) {
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
    uint8_t i, j;
    lcdClear();
    for (i = 0; i < 4; i++) {
        for (j = 0; j < strlen(helpMenuText[i]); j++) {
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


void renderGamePlayHelpMenu() {
    char* gamePlayHelp[] = {"Shoot enemies to earn", "points. Kill all ene-", "mies and go through", "door for a new level."};
    uint8_t i, j;
    lcdClear();
    for (i = 0; i < 4; i++) {
        for (j = 0; j < strlen(gamePlayHelp[i]); j++) {
            lcdWriteChar(gamePlayHelp[i][j], j * 6, i * 8);
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
    uint8_t i, j;
    lcdClear();
    for (i = 0; i < 4; i++) {
        for (j = 0; j < strlen(credits[i]); j++) {
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
    uint8_t j;
    for (j = 0; j < strlen(antiNewGame); j++) {
        lcdAntiWriteChar(antiNewGame[j], j * 6, 0);
    }
    lcdFlush();
}

static void menuOptionHelp() {
    char* antiHelp = {"Help"};
    uint8_t j;
    for (j = 0; j < strlen(antiHelp); j++) {
        lcdAntiWriteChar(antiHelp[j], j * 6, 8);
    }
    lcdFlush();
}

static void menuOptionHighscore() {
    char* antiHighscore = {"Game Play Help"};
    uint8_t j;
    for (j = 0; j < strlen(antiHighscore); j++) {
        lcdAntiWriteChar(antiHighscore[j], j * 6, 16);
    }
    lcdFlush();
}

static void menuOptionCredits() {
    char* antiCredits = {"Credits"};
    uint8_t j;
    for (j = 0; j < strlen(antiCredits); j++) {
        lcdAntiWriteChar(antiCredits[j], j * 6, 24);
    }
    lcdFlush();
}


void initMainMenu() {
    renderMainMenu();
    menuOptionNewGame();
}


uint8_t mainMenuFunction() {
    if (currentGamestate == mainMenu) {
        if (currentSelectedOption == newGame) {
            uint8_t joystickInput = processInputMainMenu();
            if (joystickInput == 1) {
                return 1;
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
                currentGamestate = gamePlayHelpMenu;
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
    return 0;
}


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

void gamePlayHelpMenuFunction() {
    if (currentGamestate == gamePlayHelpMenu) {
        renderGamePlayHelpMenu();
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





