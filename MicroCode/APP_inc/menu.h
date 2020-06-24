#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <stdint.h>

// Enumerator use to represent menu state.
typedef enum {
    mainMenu  = 0,
    helpMenu  = 1,
    gameplayMenu = 2,
    creditsMenu  = 3,
} menustate_t;

// Initializes the main menu
void initMainMenu();

// Overall menu function.
// Check which part of the menu we are currently in, and renders the current state of the menu.
// Check for input from joystick to change menu state.
// Return 1 if the "New Game" option is selected and the state is changed to game. Otherwise return 0.
uint8_t processMenu();


#endif /* MENU_H_INCLUDED */
