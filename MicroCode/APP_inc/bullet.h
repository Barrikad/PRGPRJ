#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED
#include "fix_point_math.h"
#include "entity_representation.h"

#define BULLET_SPEED 1

#define WEAPON_COOLDOWN 32

typedef struct{
    placement_t placement;
    vector_t velocity;
}bullet_t;

//hitbox radius in both directions of the bullet. currently 0.5
const vector_t BULLET_RADIUS;

//move the bullet according to its velocity
void moveBullet(bullet_t *bullet);

//create a bullet fired from a placement
void fireBulletFromPlacement(placement_t placement);


#endif /* BULLET_H_INCLUDED */
