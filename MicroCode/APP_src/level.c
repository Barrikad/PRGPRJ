#include "level.h"
#include "ansi.h"
#include "graphics.h"
#include "fix_point_math.h"
#include <stdio.h>

#define LEVEL_WIDTH 14
#define LEVEL_HEIGHT 13

// Only the characters #, % and $ are used when inspecting level data, the rest are ignored!

static const char * levelData1 =
    "##############"
    "#            #"
    "#            $"
    "#  ##%%#     $"
    "#      #     #"
    "#      #     #"
    "#     ##   e #"
    "#     #      #"
    "#     #      #"
    "# p   #%%%#  #"
    "#            #"
    "#            #"
    "##############";

static const char * levelData2 =
    "##############"
    "#            #"
    "$            #"
    "$          e #"
    "#   ######   #"
    "#            #"
    "#            #"
    "#            #"
    "#   ######   #"
    "# p          #"
    "#            #"
    "#            #"
    "##############";

// TODO: Move some of this to API?
static void drawLevel(const char * data) {
    uint8_t i, j, k, l;
    char c;
    for (i = 0; i < LEVEL_HEIGHT; i++) {
        for (j = 0; j < TILE_HEIGHT; j++) {
            for (k = 0; k < LEVEL_WIDTH; k++) {
                for (l = 0; l < TILE_WIDTH; l++) {
                    c = data[i * LEVEL_WIDTH + k];
                    if (c == '#') {
                        printf("#");
                    } else if (c == '%') {
                        printf("%%");
                    } else {
                        printf(" ");
                    }
                }
            }
            // Go back to original position
            cursorDown(1);
            cursorLeft(LEVEL_WIDTH * TILE_WIDTH);
        }
    }
}

static const char * getLevelData(level_t level) {
    switch(level) {
    case firstLevel:
        return levelData1;
    case secondLevel:
        return levelData2;
    default:
        return NULL;
    }
}

static uint8_t collisionAtPosition(const char *data, uint8_t x, uint8_t y) {
    char c = data[x * LEVEL_WIDTH + y];
    if (c == '#' || c == '%') {
        return 1;
    }
    return 0;
}

void renderLevel(level_t level) {
    clrscr();
    resetcolor();
    cursorToXY(0, 0);
    drawLevel(getLevelData(level));
}

// TODO: Move some of this to API?
uint8_t entityCollidesWall(level_t level, const placement_t *placement) {
    uint8_t i, j;
    char c;
    wallCollision collision = noCollideTopBottom | noCollideLeftRight;
    uint8_t collisionTopLeft     = 0;
    uint8_t collisionTopRight    = 0;
    uint8_t collisionBottomLeft  = 0;
    uint8_t collisionBottomRight = 0;
    const char *data = getLevelData(level);
    fix14_t top    = (*placement).position.y;
    fix14_t bottom = (*placement).position.y + (*placement).hitboxHeight;
    fix14_t left   = (*placement).position.x;
    fix14_t right  = (*placement).position.x + (*placement).hitboxWidth;
    fix14_t topDecimal    = (((top >> FIX14_SHIFT) + 1) << FIX14_SHIFT) - top;
    fix14_t bottomDecimal = ((bottom >> FIX14_SHIFT) << FIX14_SHIFT) - bottom;
    fix14_t leftDecimal   = (((left >> FIX14_SHIFT) + 1) << FIX14_SHIFT) - left;
    fix14_t rightDecimal  = ((right >> FIX14_SHIFT) << FIX14_SHIFT) - right;

    // Detect outside of map.
    if (top < 0) {
        collision |= collideTop;
    }
    if (bottom > createFix(LEVEL_HEIGHT)) {
        collision |= collideBottom;
    }
    if (left < 0) {
        collision |= collideLeft;
    }
    if (right > createFix(LEVEL_WIDTH)) {
        collision |= collideRight;
    }

    // Detect collision with walls.
    // Assumes the hitbox is smaller than the size of a wall, one unit, and
    // hence we can look only at the corners of the hitbox!
    if (collisionAtPosition(data, floorFix(top), floorFix(left))) {
        collisionTopLeft = 1;
    }
    if (collisionAtPosition(data, floorFix(top), floorFix(right))) {
        collisionTopRight = 1;
    }
    if (collisionAtPosition(data, floorFix(bottom), floorFix(left))) {
        collisionBottomLeft = 1;
    }
    if (collisionAtPosition(data, floorFix(bottom), floorFix(right))) {
        collisionBottomRight = 1;
    }

    // Four corners collide
    if (collisionTopLeft && collisionTopRight && collisionBottomLeft && collisionBottomRight) {
        // Inside box, don't know what to do...
    }
    // Three corners collide
    else if (collisionTopLeft && collisionBottomLeft && collisionTopRight) {
        collision |= collideLeft | collideTop;
    }
    else if (collisionTopLeft && collisionBottomLeft && collisionBottomRight) {
        collision |= collideLeft | collideBottom;
    }
    else if (collisionTopRight && collisionBottomRight && collisionTopLeft) {
        collision |= collideRight| collideTop;
    }
    else if (collisionTopRight && collisionBottomRight && collisionBottomLeft) {
        collision |= collideRight | collideBottom;
    }
    // Two corners collide
    else if (collisionTopLeft && collisionTopRight) {
        collision |= collideTop;
    }
    else if (collisionBottomLeft && collisionBottomRight) {
        collision |= collideBottom;
    }
    else if (collisionTopLeft && collisionBottomLeft) {
        collision |= collideLeft;
    }
    else if (collisionTopRight && collisionBottomRight) {
        collision |= collideRight;
    }
    else if (collisionTopRight && collisionBottomLeft) {
        // Can't handle these odd corners...
    }
    else if (collisionTopLeft && collisionBottomRight) {
        // Can't handle these odd corners...
    }
    // One corner collides
    else if (collisionTopLeft) {
        if (topDecimal < leftDecimal) {
            collision |= collideTop;
        } else {
            collision |= collideLeft;
        }
    }
    else if (collisionTopRight) {
        if (topDecimal < rightDecimal) {
            collision |= collideTop;
        } else {
            collision |= collideRight;
        }
    }
    else if (collisionBottomLeft) {
        if (bottomDecimal < leftDecimal) {
            collision |= collideBottom;
        } else {
            collision |= collideLeft;
        }
    }
    else if (collisionBottomRight) {
        if (bottomDecimal < rightDecimal) {
            collision |= collideBottom;
        } else {
            collision |= collideRight;
        }
    }
    // No corners collide
    else {
        // Noop
    }

    cursorToXY(LEVEL_WIDTH * TILE_WIDTH + 2 + floorFix(left * TILE_WIDTH), floorFix(top * TILE_HEIGHT));
    printf("                                   \n");
    cursorRight(LEVEL_WIDTH * TILE_WIDTH + 2 + floorFix(left * TILE_WIDTH));
    printf("                                   \n");
    cursorRight(LEVEL_WIDTH * TILE_WIDTH + 2 + floorFix(left * TILE_WIDTH));
    printf("                                   \n");
    cursorRight(LEVEL_WIDTH * TILE_WIDTH + 2 + floorFix(left * TILE_WIDTH));
    printf("                                   \n");
    cursorRight(LEVEL_WIDTH * TILE_WIDTH + 2 + floorFix(left * TILE_WIDTH));
    printf("------- %d, %d, %d, %d -------\n", collisionTopLeft, collisionTopRight, collisionBottomLeft, collisionBottomRight);
    cursorRight(LEVEL_WIDTH * TILE_WIDTH + 2 + floorFix(left * TILE_WIDTH));
    printf("------- %d, %d, %d, %d -------\n", collision & collideTop, collision & collideBottom, collision & collideLeft, collision & collideRight);
    cursorRight(LEVEL_WIDTH * TILE_WIDTH + 2 + floorFix(left * TILE_WIDTH));
    printf("                                   \n");
    cursorRight(LEVEL_WIDTH * TILE_WIDTH + 2 + floorFix(left * TILE_WIDTH));
    printf("                                   \n");
    cursorRight(LEVEL_WIDTH * TILE_WIDTH + 2 + floorFix(left * TILE_WIDTH));
    printf("                                   \n");
    cursorRight(LEVEL_WIDTH * TILE_WIDTH + 2 + floorFix(left * TILE_WIDTH));
    printf("                                   \n");
    return collision;
}
