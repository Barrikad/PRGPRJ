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

//number of registered entities
uint8_t numberOfPlayers();
uint8_t numberOfEnemies();
uint8_t numberOfBullets();

//pointer to the head of the array of entities
player_t* allPlayers();
enemy_t* allEnemies();
bullet_t* allBullets();

//decrement cooldown of all weapons
void reduceWeaponCooldowns();

#endif /* GAME_ENTITIES_H_INCLUDED */
