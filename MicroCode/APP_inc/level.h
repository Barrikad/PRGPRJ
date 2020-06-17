#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include <stdint.h>
#include "fix_point_math.h"

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
void renderLevel(level_t level);

#endif /* LEVEL_H_INCLUDED */
