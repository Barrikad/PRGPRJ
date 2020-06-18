#ifndef GAME_ENTITIES_H_INCLUDED
#define GAME_ENTITIES_H_INCLUDED
#include "collision.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"

//add entities to gamestate
void addPlayer(player_t player);
void addEnemy(enemy_t enemy);
void addBullet(bullet_t bullet);

player_t* allPlayers();

//decrement cooldown of all weapons
void reduceWeaponCooldowns();

#endif /* GAME_ENTITIES_H_INCLUDED */
