#ifndef BOSS_MODE_H_INCLUDED
#define BOSS_MODE_H_INCLUDED

#include <stdint.h>
#include "level.h"

// Renders the boss mode / HackerTyper screen. This should (FOR NOW) determine by itself how often it wants to render!
void renderBossMode(level_t currentLevel);

// Processes input from the user, changing the shown content when the user types.
// Returns 0 if should stay in boss mode, and 1 if should return to main game again.
uint8_t processInputBossMode();

// Whether the boss key has been pressed, and the boss mode should be entered.
uint8_t isBossKeyPressed();

#endif /* BOSS_MODE_H_INCLUDED */
