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
void drawSprite11(const char sprite[],placement_t placement);

//will maybe need separate, more efficient, functions for terrain


#endif /* GRAPHICS_H_INCLUDED */
