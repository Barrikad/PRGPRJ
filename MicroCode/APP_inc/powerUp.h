#ifndef POWERUP_H_INCLUDED
#define POWERUP_H_INCLUDED
#include "entity_representation.h"
//type for registering that a player has powerups, debuffs etc.
// bit1 on if powerup1 is on f.ex.
typedef uint8_t effects_t;


typedef struct{
    placement_t placement;
    effects_t effects;
}powerUp_t;


#endif /* POWERUP_H_INCLUDED */
