#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED
#include <stdio.h>
#include "fix_point_math.h"
#include "ansi.h"
#include "entity_representation.h"

#define TILE_WIDTH 4
#define TILE_HEIGHT 3

// Remove the given tank from the drawn area.
void undrawTank(const placement_t *placement);

// Draw the given tank.
void drawTank(const placement_t *placement, uint8_t color);

// Remove the given bullet from the drawn area.
void undrawBullet(const placement_t *placement);

// Draw the given player.
void drawBullet(const placement_t *placement, uint8_t color);


#endif /* GRAPHICS_H_INCLUDED */
