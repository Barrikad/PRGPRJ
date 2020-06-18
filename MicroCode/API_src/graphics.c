#include "graphics.h"

#define DIRECTIONS 4

// TODO: Use UTF-8 Unicode
// Sprite for a tank
const char TANK[DIRECTIONS][TILE_WIDTH * TILE_HEIGHT + 1] = {
    // Right
    "--- "
    " H->"
    "--- ",
    // Down
    "|  |"
    "|HH|"
    " \\/ ",
    // Left
    " ---"
    "<-H "
    " ---",
    // Up
    " /\\ "
    "|HH|"
    "|  |"};
const char TANK_CLEAR[TILE_WIDTH * TILE_HEIGHT + 1] =
    "    "
    "    "
    "    ";

// The bullet sprite
const char BULLET = 'o';

static void drawSpriteTiles(const char sprite[TILE_WIDTH * TILE_HEIGHT]) {
    uint8_t i, j;
    for (i = 0; i < TILE_HEIGHT; i++) {
        // Print all horizontal tiles
        for (j = 0; j < TILE_WIDTH; j++) {
            printf("%c", sprite[i * TILE_WIDTH + j]);
        }

        // Go down and to original x-position
        cursorDown(1);
        cursorLeft(TILE_WIDTH);
    }
}

// Go to the position from where we can start drawing
static void goToPosition(const vector_t *position) {
    uint8_t x = roundFix((*position).x * TILE_WIDTH);
    uint8_t y = roundFix((*position).y * TILE_HEIGHT);
    cursorToXY(x, y);
}

void undrawTank(const placement_t *placement) {
    goToPosition(&(*placement).position);
    drawSpriteTiles(TANK_CLEAR);
}

void drawTank(const placement_t *placement, uint8_t color) {
    goToPosition(&(*placement).position);
    //reduce angle so that 0 <= rotation < 512
    //multiply by four to choose sprite
    //divide by 512 to get 0 <= rotationOffset < 4
    uint8_t rotationOffset = roundFix(((DIRECTIONS * ((*placement).rotation & 511)) << 14)/512);
    rotationOffset %= DIRECTIONS;
    fgcolor(color);
    drawSpriteTiles(TANK[rotationOffset]);
    resetcolor();
}

void undrawBullet(const placement_t *placement) {
    goToPosition(&(*placement).position);
    printf(" ");
}

void drawBullet(const placement_t *placement, uint8_t color) {
    goToPosition(&(*placement).position);
    // TODO: Draw bullet with different character depending on where it is.
    // For example draw as "." if it's in the bottom of a character and as "\" if its in the top.
    fgcolor(color);
    printf("%c", BULLET);
    resetcolor();
}
