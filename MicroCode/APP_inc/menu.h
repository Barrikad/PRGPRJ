#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <stdint.h>

// Enumerator use to represent menu state.
typedef enum {
    game      = 0,
    mainMenu  = 1,
    helpMenu  = 2,
    gameplayMenu = 3,
    creditsMenu  = 4,
    bossMode  = 5
} menustate_t;

// Initializes the main menu
void initMainMenu();

// Overall main menu function
// Check which part of the menu we are currently in and renders the current state of the menu.
// Check for input from joystick to change menu state.
// Return 1 if the "New Game" option is selected and the state is changed to game. Otherwise return 0.
uint8_t mainMenuFunction();

// Render the help menu.
// Check for joystick input to change menu state.
void helpMenuFunction();
// Render the gameplay menu
// Check for joystick input to change menu state
void gamePlayHelpMenuFunction();
// Render credits menu.
// Check for joystick input to change menu state
void creditsMenuFunction();


#endif /* MENU_H_INCLUDED */
