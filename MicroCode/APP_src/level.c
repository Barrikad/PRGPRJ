#include "level.h"
#include "ansi.h"
#include "graphics.h"
#include "fix_point_math.h"
#include <stdio.h>

#define LEVEL_WIDTH 42
#define LEVEL_HEIGHT 13

// Only the characters #, % and d are used when inspecting level data, the rest are ignored!

static const char * levelDataStart =
    "##########################################"
    "d   #             #       #       #      #"
    "d p #             #     $ #       #      #"
    "#   #   #####     #   #   #   #   #      #"
    "#   #       #         #       #          #"
    "#   #       #         #       #          #"
    "#   #            ###################     #"
    "#   #   #          c                  c  #"
    "#   #   #                                #"
    "#       #      ###   ################ e  #"
    "#       #          c                  c  #"
    "#       #                                #"
    "######################################dd##";

static const char * levelDataBlock =
    "######################################dd##"
    "d  c #         c     ##        c #### p  #"
    "d  e #              c             ###    #"
    "#   ## c      #####  $ ######      ##    #"
    "#c  #       ##################     ##    #"
    "#  ##     #####################    ##    #"
    "#  #      #####################    ###   #"
    "#  #  c    ####################   c ##   #"
    "#  #         ##    #########        ##   #"
    "#  ###             ####                  #"
    "#c           c   e                       #"
    "#        ###                 c  ##       #"
    "##########################dd##############";

static const char * levelDataMaze =
    "##########################dd##############"
    "d e   #       #          #p              #"
    "d     # ## ## # ## ### # #  # #### ##### #"
    "##### # ## #  # ## #   # #### #    #     #"
    "#   # # #  # ## #  # ###      # #### #####"
    "# # # # #### #  # ## # ########    #     #"
    "# # # ####     ## #  #        # ## ##### #"
    "# # #    #######  # #########    #     # #"
    "# # ####      ## ####       ########## # #"
    "# #    ### ## #  #    #####    #   # #   #"
    "# ######## ## #### ####   #### # # # ### #"
    "#           #      #    #        #       #"
    "##########################################";

// Nowhere to hide, haha!!!
static const char * levelDataChaos =
    "##########################################"
    "#                                      p d"
    "#   e                c                   d"
    "#                                        #"
    "#                                        #"
    "#                    e                   #"
    "#                                        #"
    "#                                        #"
    "#             c      c      c            #"
    "#                                        #"
    "#   e                c             e     #"
    "#                                        #"
    "##########################################";

// Cyan
#define levelColor 6

static const char * getLevelData(level_t level) {
    switch(level) {
    case invalidLevel:
        return NULL;
    case initialLevel:
        return levelDataStart;
    case blockLevel:
        return levelDataBlock;
    case mazeLevel:
        return levelDataMaze;
    case chaosLevel:
        return levelDataChaos;
    default:
        return NULL;
    }
}

void renderLevel(level_t level) {
    uint8_t i, j;
    char c;
    const char * data = getLevelData(level);
    for (i = 0; i < LEVEL_HEIGHT; i++) {
        for (j = 0; j < LEVEL_WIDTH; j++) {
            c = data[i * LEVEL_WIDTH + j];
            if (c == '#') {
                drawWall(j, i, levelColor);
            } else if (c == '%') {
                drawBox(j, i, levelColor);
            } else {
                // Noop
            }
        }
    }
}

static uint8_t collisionAtPosition(const char *data, uint8_t x, uint8_t y) {
    char c = data[x * LEVEL_WIDTH + y];
    if (c == '#' || c == '%' || c == 'd') { // Handle collisions with doors as well!
        return 1;
    }
    return 0;
}

// TODO: Move some of this to API?
levelCollision_t entityCollidesWall(level_t level, const placement_t *placement) {
    levelCollision_t collision = noCollide;
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
    fix14_t bottomDecimal  = bottom - ((bottom >> FIX14_SHIFT) << FIX14_SHIFT);
    fix14_t leftDecimal   = (((left >> FIX14_SHIFT) + 1) << FIX14_SHIFT) - left;
    fix14_t rightDecimal  = right - ((right >> FIX14_SHIFT) << FIX14_SHIFT);

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
        collision |= collideLeft | collideRight | collideTop | collideBottom;
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

//    cursorToXY(LEVEL_WIDTH * TILE_WIDTH + 2 + floorFix(left * TILE_WIDTH), floorFix(top * TILE_HEIGHT));
//    printf("                                   \n");
//    cursorRight(LEVEL_WIDTH * TILE_WIDTH + 2 + floorFix(left * TILE_WIDTH));
//    printf("                                   \n");
//    cursorRight(LEVEL_WIDTH * TILE_WIDTH + 2 + floorFix(left * TILE_WIDTH));
//    printf("                                   \n");
//    cursorRight(LEVEL_WIDTH * TILE_WIDTH + 2 + floorFix(left * TILE_WIDTH));
//    printf("                                   \n");
//    cursorRight(LEVEL_WIDTH * TILE_WIDTH + 2 + floorFix(left * TILE_WIDTH));
//    printf("------- %d, %d, %d, %d -------\n", collisionTopLeft, collisionTopRight, collisionBottomLeft, collisionBottomRight);
//    cursorRight(LEVEL_WIDTH * TILE_WIDTH + 2 + floorFix(left * TILE_WIDTH));
//    printf("------- %d, %d, %d, %d -------\n", collision & collideTop, collision & collideBottom, collision & collideLeft, collision & collideRight);
//    cursorRight(LEVEL_WIDTH * TILE_WIDTH + 2 + floorFix(left * TILE_WIDTH));
//    printf("                                   \n");
//    cursorRight(LEVEL_WIDTH * TILE_WIDTH + 2 + floorFix(left * TILE_WIDTH));
//    printf("                                   \n");
//    cursorRight(LEVEL_WIDTH * TILE_WIDTH + 2 + floorFix(left * TILE_WIDTH));
//    printf("                                   \n");
//    cursorRight(LEVEL_WIDTH * TILE_WIDTH + 2 + floorFix(left * TILE_WIDTH));
//    printf("                                   \n");
    return collision;
}
