#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <stdint.h>

typedef enum {
    game      = 0,
    mainMenu  = 1,
    helpMenu  = 2,
    scoreMenu = 3,
    creditsMenu  = 4,
    bossMode  = 5
    // miniGame = 6;
} menustate_t;


void initMainMenu();

void mainMenuFunction();
void helpMenuFunction();
void scoreMenuFunction();
void creditsMenuFunction();


#endif /* MENU_H_INCLUDED */
