#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED
#include "fix_point_math.h"
#include "ansi.h"

//1x1 sprites - 4 rotations
const char player[];
const char bullet[];
//1x2 sprites
//2x1 sprites
//2x2 sprites

//draws sprite at position with hardware components
//should translation from game coordinates to screen coordinates be done here or in APP?
//position is position of middle of sprite?
void drawSprite11(char sprite[], vector_t position, deg512_t rotation);

//will maybe need separate, more efficient, functions for terrain


#endif /* GRAPHICS_H_INCLUDED */
