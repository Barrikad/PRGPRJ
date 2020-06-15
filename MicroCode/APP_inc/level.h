#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include <stdint.h>

typedef enum uint8_t {
    firstLevel = 0,
    secondLevel = 1,
} level_t;

// Initialize / enter the given level.
// TODO: This should change SOME timer, maybe the Enemy-AI timer?
void enterLevel(level_t level);

// Renders the current level. This should (FOR NOW) determine by itself how often it wants to render!
void renderLevel();

// Processes input from the user, changing the current level state?
// TODO: What should this return?
void processInputLevel();

#endif /* LEVEL_H_INCLUDED */
