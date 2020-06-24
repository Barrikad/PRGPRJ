#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include <stdint.h>
#include "entity_representation.h"

typedef enum {
    invalidLevel = 0,
    firstLevel = 1,
    secondLevel = 2,
    thirdLevel = 3,
} level_t;

// Determines what kind of collision happened:
// - Bit 1 is set if the collision is with the top side of a wall.
// - Bit 2 is set if the collision is with the bottom side of a wall.
// - Bit 3 is set if the collision is with the left side of a wall.
// - Bit 4 is set if the collision is with the right side of a wall.
typedef uint8_t levelCollision_t;

#define noCollide          0x00
#define collideTop         0x01
#define collideBottom      0x02
#define collideLeft        0x04
#define collideRight       0x08

// Initialize / enter the given level.
void renderLevel(level_t level);

// Detect whether a player touches a door.
// TODO: Change return type so caller know which level to enter?
// uint8_t playerTouchesDoor(const placement_t *placement);

// Detect whether and how an entity collides with a wall.
// This does no attempt to move the entity back or bounce it.
levelCollision_t entityCollidesWall(level_t level, const placement_t *placement);

#endif /* LEVEL_H_INCLUDED */
