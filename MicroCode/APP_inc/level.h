#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include <stdint.h>
#include "entity_representation.h"

typedef enum {
    firstLevel = 0,
    secondLevel = 1,
} level_t;

typedef uint8_t wallCollision;

#define noCollideTopBottom 0x00
#define collideTop         0x01
#define collideBottom      0x02

#define noCollideLeftRight 0x00
#define collideLeft        0x10
#define collideRight       0x20

// Initialize / enter the given level.
void renderLevel(level_t level, uint8_t doorsOpen);

// Detect whether a player touches a door.
// TODO: Change return type so caller know which level to enter?
// uint8_t playerTouchesDoor(const placement_t *placement);

// Detect whether an entity collides with a wall.
// Returns a value based on where the collision happens:
// - 1 if the collision is with the top side of a wall.
// - 2 if the collision is with the right side of a wall.
// - 4 if the collision is with the bottom side of a wall.
// - 8 if the collision is with the left side of a wall.
// TODO: Maybe allow returning 3 if collides with both top side and right side?
// This does no attempt to move the entity back or bounce it.
wallCollision entityCollidesWall(level_t level, const placement_t *placement);

#endif /* LEVEL_H_INCLUDED */
