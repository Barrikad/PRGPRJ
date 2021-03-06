#ifndef GAME_ENTITIES_H_INCLUDED
#define GAME_ENTITIES_H_INCLUDED
#include "collision.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"

// Enter / initialize the given level.
// TODO: This should change SOME timer, maybe the Enemy-AI timer?
void initLevel(level_t level);

//add entities to gamestate
void addPlayer(vector_t position, deg512_t rotation, action_t (*inputFunction)());
void addEnemy(vector_t position, deg512_t rotation);
void addBullet(bullet_t bullet);
void addPowerUp(vector_t position, effects_t effect);

void deletePowerUp(uint8_t index);
void deleteBullet(bullet_t *bullet);

void renderPowerUps();


// Run one tick of the main game loop.
level_t processGameTick(level_t level);



#endif /* GAME_ENTITIES_H_INCLUDED */
