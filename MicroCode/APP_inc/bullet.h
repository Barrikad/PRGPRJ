#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED
#include "fix_point_math.h"
#include "entity_representation.h"
#include "level.h"

#define WEAPON_COOLDOWN 32

typedef struct{
    placement_t placement;
    vector_t velocity;
}bullet_t;

//move the bullet according to its velocity
void moveBullet(bullet_t *bullet);

//create a bullet fired from a placement, with standard velocity
void fireBulletFromPlacement(const placement_t *placement);

//create a bullet fired from a placement, with specified velocity
void fireBulletFromPlacementWithVelocity(const placement_t *placement, fix14_t velocity);

// Detect and handle collision with wall.
// Returns true if the bullet should be deleted.
// TODO: Name this better!
uint8_t bulletCollideWallAndShouldDelete(level_t level, bullet_t *bullet);

#endif /* BULLET_H_INCLUDED */
