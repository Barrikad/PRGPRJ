#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include <stdint.h>
#include "fix_point_math.h"

//type for registering that a player has powerups, debuffs etc.
// bit1 on if powerup1 is on f.ex.
typedef uint8_t effects_t;

typedef struct{
    vector_t position;
    vector_t velocity;
    deg512_t rotation;
    uint8_t lives;
    uint8_t points;
    effects_t effects;
}player_t;

//adds velocity to player coordinates
//  Side effects: players position is changed
void movePlayer(player_t *player);

//sets players velocity to new vector
//  Side effects: players velocity is changed
void setPlayerVelocity(player_t *player, vector_t velocity);

//reduce the players lives by a given amount
//  Side effects: players total lives is reduced
void damagePlayer(player_t *player, uint8_t damage);

void fireBullet(player_t *player);

#endif /* PLAYER_H_INCLUDED */
