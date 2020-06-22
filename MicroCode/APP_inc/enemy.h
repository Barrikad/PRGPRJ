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

//fire a bullet from an enemy
void fireBulletFromEnemy(enemy_t* enemies, uint8_t index);

// Detect and handle collision with bullet.
// TODO: Fix need to pass all players down here!
void enemyCollideBullet(player_t *players, enemy_t *enemy, bullet_t *bullet);

// Detect and handle collision with player.
void enemyCollidePlayer(enemy_t *enemy, player_t *player);

// Detect and handle collision with wall.
void enemyCollideWall(level_t level, enemy_t *enemy);

#endif /* ENEMY_H_INCLUDED */
