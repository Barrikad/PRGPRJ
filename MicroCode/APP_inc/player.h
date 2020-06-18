#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include <stdint.h>
#include "fix_point_math.h"
#include "entity_representation.h"
#include "movement.h"

//type for registering that a player has powerups, debuffs etc.
// bit1 on if powerup1 is on f.ex.
typedef uint8_t effects_t;

typedef struct{
    placement_t placement;
    vector_t velocity;
    uint8_t lives;
    uint8_t points;
    uint8_t weaponCooldown;
    effects_t effects;
}player_t;

// Initialize a player with the given position and rotation.
void initPlayer(player_t *player, vector_t position, deg512_t rotation);

//adds velocity to player coordinates
//  Side effects: players position is changed
void movePlayer(player_t *player);

//fire bullet from players placement
void fireBulletFromPlayer(player_t* player);

#endif /* PLAYER_H_INCLUDED */
