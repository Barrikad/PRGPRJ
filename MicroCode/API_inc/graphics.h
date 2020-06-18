#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED
#include <stdio.h>
#include "fix_point_math.h"
#include "ansi.h"
#include "entity_representation.h"

#define TILE_WIDTH 4
#define TILE_HEIGHT 3

// Draw the given player.
void undrawPlayer(const placement_t *placement);

// Draw the given player.
void drawPlayer(const placement_t *placement);

// Draw the given bullet.
void undrawBullet(const placement_t *placement);

// Draw the given player.
void drawBullet(const placement_t *placement);


#endif /* GRAPHICS_H_INCLUDED */
