#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED
#include <stdint.h>
#include "entity_representation.h"
#include "fix_point_math.h"

typedef struct{
    placement_t placement;
    vector_t velocity;
    uint8_t lives;
    uint8_t points;
} enemy_t;

//move an enemy according to its velocity
void moveEnemy(enemy_t *enemy);

//fire a bullet from an enemy
void fireBulletEnemy(enemy_t enemy);

#endif /* ENEMY_H_INCLUDED */
