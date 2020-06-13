#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

//draws sprite at position with hardware components
//should translation from game coordinates to screen coordinates be done here or in APP?
void drawSprite(uint8_t spriteID, vector_t position);

//will maybe need separate, more efficient, functions for terrain


#endif /* GRAPHICS_H_INCLUDED */
