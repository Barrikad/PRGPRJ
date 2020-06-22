#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED
#include "fix_point_math.h"
#include "entity_representation.h"
#include "level.h"

#define WEAPON_COOLDOWN 32

//type for storing information about the shooter of a bullet
//  0=undefined, 1=player1, 2=player2, 3=player3, 4=player4,
//    5=enemy
typedef uint8_t shotBy_t;

typedef struct{
    placement_t placement;
    vector_t velocity;
    shotBy_t shotBy;
}bullet_t;

//move the bullet according to its velocity
void moveBullet(bullet_t *bullet);

//create a bullet fired from a placement, with standard velocity
void fireBulletFromPlacement(const placement_t *placement, shotBy_t shotBy);

//create a bullet fired from a placement, with specified velocity
void fireBulletFromPlacementWithVelocity(const placement_t *placement, fix14_t velocity, shotBy_t shotBy);

// Detect and handle collision with wall.
// Returns true if the bullet should be deleted.
// TODO: Name this better!
uint8_t bulletCollideWallAndShouldDelete(level_t level, bullet_t *bullet);

#endif /* BULLET_H_INCLUDED */
