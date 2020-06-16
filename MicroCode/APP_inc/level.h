#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include <stdint.h>
#include "fix_point_math.h"

#define LEVEL_WIDTH 128
#define LEVEL_HEIGHT 64
#define VERTICAL_OFFSET 0
#define HORIZONTAL_OFFSET 0

typedef enum {
    firstLevel = 0,
    secondLevel = 1,
} level_t;

//returns x-coordinates of the level bounds
vector_t verticalBound();

//returns y-coordinates of the level bounds
vector_t horizontalBound();

// Initialize / enter the given level.
// TODO: This should change SOME timer, maybe the Enemy-AI timer?
void enterLevel(level_t level);

// Renders the current level. This should (FOR NOW) determine by itself how often it wants to render!
void renderLevel();

// Processes input from the user, changing the current level state?
// TODO: What should this return?
void processInputLevel();

#endif /* LEVEL_H_INCLUDED */
