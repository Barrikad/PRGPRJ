#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED
#include <stdio.h>
#include "fix_point_math.h"
#include "ansi.h"
#include "entity_representation.h"

#define TILE_WIDTH 4
#define TILE_HEIGHT 3

// Check if should re-draw the tank based on the given position.
uint8_t shouldRedraw(const placement_t *previousPlacement, const placement_t *currentPlacement);

// Remove the given tank from the drawn area.
void undrawTank(const placement_t *placement);

// Draw the given tank.
void drawTank(const placement_t *placement, uint8_t color);

// Draw a wall at the given location.
void drawWall(uint8_t x, uint8_t y, uint8_t color);

// Draw a box at the given location.
void drawBox(uint8_t x, uint8_t y, uint8_t color);

// Draw the given door.
// If `open` is 1, the door is drawn open, else it's drawn closed.
void drawDoor(const placement_t *placement, uint8_t color, uint8_t open);

// Remove power up from location
void undrawPowerUp(const placement_t *placement);

// Draw power up at location
void drawPowerUp(const placement_t *placement, uint8_t color, uint8_t blinkOn);

// Remove the given bullet from the drawn area.
void undrawBullet(const placement_t *placement);

// Draw the given player.
void drawBullet(const placement_t *placement, uint8_t color);


#endif /* GRAPHICS_H_INCLUDED */
