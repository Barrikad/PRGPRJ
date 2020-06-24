#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <stdint.h>

typedef enum {
    game      = 0,
    mainMenu  = 1,
    helpMenu  = 2,
    gamePlayHelpMenu = 3,
    creditsMenu  = 4,
    bossMode  = 5
    // miniGame = 6;
} menustate_t;


void initMainMenu();

uint8_t mainMenuFunction();
void helpMenuFunction();
void gamePlayHelpMenuFunction();
void creditsMenuFunction();


#endif /* MENU_H_INCLUDED */
