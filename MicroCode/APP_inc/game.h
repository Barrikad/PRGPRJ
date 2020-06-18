#ifndef GAME_ENTITIES_H_INCLUDED
#define GAME_ENTITIES_H_INCLUDED
#include "collision.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"

//add entities to gamestate
void addPlayer(vector_t position, deg512_t rotation, action_t (*inputFunction)());
void addEnemy(enemy_t enemy);
void addBullet(bullet_t bullet);

//decrement cooldown of all weapons
void reduceWeaponCooldowns();

// Run one tick of the main game loop.
void processGameTick();

#endif /* GAME_ENTITIES_H_INCLUDED */
