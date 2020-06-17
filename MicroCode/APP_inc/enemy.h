#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED
#include <stdint.h>
#include "entity_representation.h"
#include "fix_point_math.h"

typedef struct{
    placement_t placement;
    uint8_t lives;
    uint8_t points;
    uint8_t weaponCooldown;
} enemy_t;

//fire a bullet from an enemy
void fireBulletEnemy(enemy_t* enemy);

#endif /* ENEMY_H_INCLUDED */
