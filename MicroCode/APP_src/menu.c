#include <stdio.h>
#include <string.h>
#include "lcd.h"
#include "player.h"
#include "game.h"
#include "menu.h"
#include "falling_edge_selection.h"
#include "player_stat_graphics.h"

// Enumerator to represent the selected option on the main menu.
typedef enum {
    newGame    = 0,
    help  = 1,
    gameplay  = 2,
    credits = 3
} selectedOption_t;

static menustate_t currentGamestate = mainMenu;
static selectedOption_t currentSelectedOption = newGame;

// Render Main Menu down to LCD.
static void renderMainMenu() {
    char* newGame[] = {"New Game     ->Select", "Help         <-Back", "Gameplay", "Credits"};
    uint8_t i, j;
    lcdClear();
    for (i = 0; i < 4; i++) {
        for (j = 0; j < strlen(newGame[i]); j++) {
            lcdWriteChar(newGame[i][j], j * 6, i * 8);
        }
    }
    lcdFlush();
}

// Processes the input from the joystick in the main menu.
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

// Render the help menu down to LCD.
static void renderHelpMenu() {
    // TODO: This!
    char* helpMenuText[] = {"Up/down to move.", "Left/right to rotate.", "Shoot by pressing", "the joystick down."};
    uint8_t i, j;
    lcdClear();
    for (i = 0; i < 4; i++) {
        for (j = 0; j < strlen(helpMenuText[i]); j++) {
            lcdWriteChar(helpMenuText[i][j], j * 6, i * 8);
        }
    }
    lcdFlush();
}

// Processes the input from the joystick in the help menu.
uint8_t processInputHelpMenu() {
    if (hasPressedLeft()) {
        return 1;
    }
    return 0; // Stays in submenu
}

// Render the game play help menu down to the LCD.
void renderGameplayMenu() {
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

// Processes the input from the joystick in the score menu.
uint8_t processInputScoreMenu() {
    if (hasPressedLeft()) {
        return 1;
    }
    return 0; // Stays in submenu
}

// Render the credits menu down to the LCD.
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

// Processes the input from the joystick in the credits menu.
uint8_t processInputCreditsMenu() {
    if (hasPressedLeft()) {
        return 1;
    }
    return 0;
}


// The following functions starting with menuOption highlights
// currently hovered option on the main menu. This is done by
// inverting the color of the option.

// inverting color of New Game
static void menuOptionNewGame() {
    char* antiNewGame = {"New Game"};
    uint8_t j;
    for (j = 0; j < strlen(antiNewGame); j++) {
        lcdAntiWriteChar(antiNewGame[j], j * 6, 0);
    }
    lcdFlush();
}

// inverting color of Help
static void menuOptionHelp() {
    char* antiHelp = {"Help"};
    uint8_t j;
    for (j = 0; j < strlen(antiHelp); j++) {
        lcdAntiWriteChar(antiHelp[j], j * 6, 8);
    }
    lcdFlush();
}

// inverting color of Game Play Help
static void menuOptionHighscore() {
    char* antiHighscore = {"Gameplay"};
    uint8_t j;
    for (j = 0; j < strlen(antiHighscore); j++) {
        lcdAntiWriteChar(antiHighscore[j], j * 6, 16);
    }
    lcdFlush();
}

// inverting color of Credits
static void menuOptionCredits() {
    char* antiCredits = {"Credits"};
    uint8_t j;
    for (j = 0; j < strlen(antiCredits); j++) {
        lcdAntiWriteChar(antiCredits[j], j * 6, 24);
    }
    lcdFlush();
}


// Initializes the main menu
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
                currentSelectedOption = gameplay;
                renderMainMenu();
                menuOptionHighscore();
            }
            else if (joystickInput == 3) {
                currentSelectedOption = newGame;
                renderMainMenu();
                menuOptionNewGame();
            }
        }
        else if (currentSelectedOption == gameplay) {
            uint8_t joystickInput = processInputMainMenu();
            if (joystickInput == 1) {
                currentGamestate = gameplayMenu;
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
                currentSelectedOption = gameplay;
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
    if (currentGamestate == gameplayMenu) {
        renderGameplayMenu();
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





