#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED
#include <stdio.h>
#include "fix_point_math.h"
#include "ansi.h"
#include "entity_representation.h"

//1x1 sprites - 4 rotations
const char PLAYER[4];
const char BULLET[4];
const char ENEMY[4];
//1x2 sprites
//2x1 sprites
//2x2 sprites

//draws sprite at position with hardware components
//should translation from game coordinates to screen coordinates be done here or in APP?
//position is position of middle of sprite?
void drawSprite11(const char sprite[], const placement_t *placement);

// Draw the given player.
void undrawPlayer(const placement_t *placement);

// Draw the given player.
void drawPlayer(const placement_t *placement);

// Draw the given bullet.
void undrawBullet(const placement_t *placement);

// Draw the given player.
void drawBullet(const placement_t *placement);


#endif /* GRAPHICS_H_INCLUDED */
