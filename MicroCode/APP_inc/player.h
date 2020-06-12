#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include <stdint.h>
#include "fix_point_math.h"

typedef struct{
    vector_t position;
    vector_t velocity;
    uint8_t lives;
    uint8_t points;
}player_t;

//adds velocity to player coordinates
//  Side effects: players position is changed
void movePlayer(player_t *player);

//sets players velocity to new vector
//  Side effects: players velocity is changed
void setPlayerVelocity(player_t *player, vector_t velocity);

//reduce the players lives by a given amount
//  Side effects: players total lives is reduced
void reducePlayerLives(player_t *player, uint8_t damage);

#endif /* PLAYER_H_INCLUDED */
