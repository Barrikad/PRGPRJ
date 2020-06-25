#ifndef BOSS_MODE_H_INCLUDED
#define BOSS_MODE_H_INCLUDED

#include <stdint.h>
#include "level.h"

// Initializes / enters the boss mode.
void initBossMode();

// Processes input from the user, changing the shown content when the user types.
// Returns 0 if should stay in boss mode, and 1 if should return to main game again.
uint8_t processBossMode();

// Whether the boss key has been pressed, and the boss mode should be entered.
uint8_t isBossKeyPressed();

#endif /* BOSS_MODE_H_INCLUDED */
