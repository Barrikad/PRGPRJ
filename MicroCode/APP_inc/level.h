#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include <stdint.h>

typedef enum {
    firstLevel = 0,
    secondLevel = 1,
} level_t;

// Initialize / enter the given level.
// TODO: This should change SOME timer, maybe the Enemy-AI timer?
void renderLevel(level_t level);

#endif /* LEVEL_H_INCLUDED */
