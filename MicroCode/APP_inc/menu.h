#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <stdint.h>

// Renders the help screen. This should (FOR NOW) determine by itself how often it wants to render!
void renderMainMenu();

// Processes input from the user, possibly changing the currently selected item?
// Returns 0 if should stay in main menu, 1 if should start game, 2 if should move to help menu and 3 if should start minigame.
uint8_t processInputMainMenu();

// Renders the help screen. This should (FOR NOW) determine by itself how often it wants to render!
void renderHelpMenu();

// Processes input from the user, possibly scrolling down the content?
// Returns 0 if should stay in help menu, 1 if should return to main menu.
uint8_t processInputHelpMenu();

// Renders the score screen. This should (FOR NOW) determine by itself how often it wants to render!
// TODO: Inputs to this function!
void renderScoreMenu(uint8_t clearedLevels);

// Processes input from the user.
// Returns 0 if should stay in score menu, 1 if should return to main menu.
uint8_t processInputScoreMenu();

// Renders the credits screen. This should (FOR NOW) determine by itself how often it wants to render!
void renderCreditsMenu();

#endif /* MENU_H_INCLUDED */
