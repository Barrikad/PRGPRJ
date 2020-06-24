#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED
#include <stdint.h>
#include "entity_representation.h"
#include "fix_point_math.h"
#include "player.h"
#include "level.h"
#include "bullet.h"

#define CHECKPOINT_COUNT 8

typedef struct{
    placement_t placement;
    uint8_t lives;
    uint8_t weaponCooldown;
    uint8_t points;
    uint8_t checkpointIndex;
} enemy_t;

// Initialize an enemy.
void initEnemy(enemy_t *enemy, vector_t position, deg512_t rotation);

//fire a bullet from an enemy
void fireBulletFromEnemy(enemy_t* enemies, uint8_t index);

// Detect and handle collision with bullet.
// TODO: Fix need to pass all players down here!
uint8_t enemyCollideBullet(player_t *players, enemy_t *enemy, bullet_t *bullet);

#endif /* ENEMY_H_INCLUDED */
