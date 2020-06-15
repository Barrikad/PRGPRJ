#ifndef GAME_ENTITIES_H_INCLUDED
#define GAME_ENTITIES_H_INCLUDED
#include "collision.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"

//add entities to gamestate
void addPlayer(player_t *player);
void addEnemy(enemy_t *enemy);
void addBullet(bullet_t *bullet);

//move game entities
void movePlayers();
void moveEnemies();
void moveBullets();

//number of registered entities
uint8_t numberOfPlayers();
uint16_t numberOfEnemies();
uint16_t numberOfBullets();

player_t** allPlayers();
player_t** allEnemies();
player_t** allBullets();

void processCollisions();

#endif /* GAME_ENTITIES_H_INCLUDED */
