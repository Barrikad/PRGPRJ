#include <stdio.h>
#include <string.h>
#include "lcd.h"
#include "joystick.h"
#include "player.h"
#include "game_state.h"
#include "menu.h"


typedef struct {
    const char * options;
    int8_t layer;

} menu_t;


void setMenuOptions(menu_t menu) {
    //*menu.options = {"New Game", "Help", "Highscore", "Credits"};

}



void renderMainMenu() {
    char* newGame[] = {"New Game     ->Select", "Help", "Highscore", "Credits"};
    lcdClear();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < strlen(newGame[i]); j++) {
            lcdWriteChar(newGame[i][j], j * 6, i * 8);
        }
    }
    lcdFlush();
}

uint8_t processInputMainMenu() {

    // TODO: This!
    return 0;
}

void renderHelpMenu() {
    // TODO: This!
    char* helpMenuText[] = {"Control the tank with", "the joystick.", "Shoot by pressing the", "joystick down. <-Back"};
    lcdClear();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < strlen(helpMenuText[i]); j++) {
            lcdWriteChar(helpMenuText[i][j], j * 6, i * 8);
        }
    }
    lcdFlush();
}

/*
uint8_t processInputHelpMenu() {
    if (JOYSTICK_LEFT) {
        if (JOYSTICK_MIDDLE)
            return 1; //returns to main menu
        }
    }
    return 0; // Stays in submenu
}
*/

void scoreFormatting(char score[3][14], player_t* players, uint8_t numPlayers){
    for (int i = 0; i < numPlayers; i++) {
        sprintf(score[i], "%13d",players[i].points);
    }
}

void renderScoreMenu(uint8_t clearedLevels) {
    uint8_t numPlayers = numberOfPlayers();
    char* highscore = "      Highscore      ";
    char* playerNumber[] = {"Player 1", "Player 2", "Player 3"}; // if more than 3 players is wanted then a scroll function is needed
    player_t* players = allPlayers();
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



/*
static uint8_t lastJoystickLeft;

uint8_t processInputScoreMenu() {
    uint8_t currentJoystickLeft = ...;
    if (lastJoystickLeft && !currentJoystickLeft) {
        // Falling edge of JOYSTICK_LEFT
    }
    lastJoystickLeft = currentJoystickLeft;
    return 0;
     if (JOYSTICK_LEFT) {
        if (JOYSTICK_MIDDLE)
            return 1; //returns to main menu
        }
    }
    return 0; // Stays in submenu

}
*/
void renderCreditsMenu() {
    char* credits[] = {"Created by:","Mads Marquart", "Simon Tobias Lund", "Gustav Leth-Espensen"};
    lcdClear();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < strlen(credits[i]); j++) {
            lcdWriteChar(credits[i][j], j * 6, i * 8);
        }
    }
    lcdFlush();
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


