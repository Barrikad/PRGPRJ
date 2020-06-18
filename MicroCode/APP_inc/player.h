#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include <stdint.h>
#include "fix_point_math.h"
#include "entity_representation.h"
#include "movement.h"

//notes on the goals of the architecture:
//  arbitrary number of players with arbitrary input devices
//  arbitrary number of enemies with arbitrary input devices
//  can have one function for each menu-like feature, but input should
//    be arbitrary
//this is extra important as we have not really yet decided on a final input method (13/06)

//type for registering that a player has powerups, debuffs etc.
// bit1 on if powerup1 is on f.ex.
typedef uint8_t effects_t;

typedef struct {
    placement_t placement;
    vector_t velocity;
    uint8_t lives;
    uint8_t points;
    uint8_t weaponCooldown;
    effects_t effects;
    action_t (*inputFunction)();
} player_t;

// Initialize a player with the given position, rotation and input function.
void initPlayer(player_t *player, vector_t position, deg512_t rotation, action_t (*inputFunction)());

//adds velocity to player coordinates
//  Side effects: players position is changed
void movePlayer(player_t *player);

//fire bullet from players placement
void fireBulletFromPlayer(player_t* player);

// Get input from player input devices and realize the mapped actions
void processPlayerActionsInGame(player_t *player);

#endif /* PLAYER_H_INCLUDED */
