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

void renderLevel(level_t level) {
    clrscr();
    cursorToXY(0, 0);
    drawLevel(getLevelData(level));
}

// TODO: Move some of this to API?
uint8_t entityCollidesWall(level_t level, const placement_t *placement) {
    uint8_t i, j;
    char c;
    const char *data = getLevelData(level);
    fix14_t top    = (*placement).position.y;
    fix14_t bottom = (*placement).position.y + (*placement).hitboxHeight;
    fix14_t left   = (*placement).position.x;
    fix14_t right  = (*placement).position.x + (*placement).hitboxWidth;

    // Detect outside of map.
    if (top < 0) {
        return 1;
    }
    if (bottom > createFix(LEVEL_HEIGHT)) {
        return 1;
    }
    if (left < 0) {
        return 1;
    }
    if (right > createFix(LEVEL_WIDTH)) {
        return 1;
    }

    // Detect collision with walls
    // TODO: Remove breaking / returning out of loop!
    for (i = floorFix(top); i <= floorFix(bottom); i++) {
        for (j = floorFix(left); j <= floorFix(right); j++) {
            c = data[i * LEVEL_WIDTH + j];
            if (c == '#') {
                return 1;
            }
            if (c == '%') {
                return 1;
            }
        }
    }

    return 0;
}
