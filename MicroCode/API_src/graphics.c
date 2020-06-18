#include "graphics.h"

#define DIRECTIONS 4

//0-right, 1-down, 2-left, 3-up
const char PLAYER[DIRECTIONS] = {195,194,180,193};
const char BULLET = 111;
const char ENEMY[DIRECTIONS] = {204,203,185,202};

static void drawSpriteTiles(const char tiles[], uint8_t height, uint8_t width) {
    for(int i = 0; i < height; i++){
        //print all horizontal tiles
        for(int j = 0; j < width; j++){
            printf("\%c",tiles[i + j]);
        }

        //go down and to original x-position
        cursorDown(1);
        cursorLeft(width);
    }
}

// Go to the position from where we can start drawing
static void goToPosition(const vector_t *position) {
    // Rounding here is correct!
    uint8_t x = roundFix((*position).x);
    uint8_t y = roundFix((*position).y);
    cursorToXY(x, y);
}

void undrawPlayer(const placement_t *placement) {
    goToPosition(&(*placement).position);
    printf(" ");
}

void drawPlayer(const placement_t *placement) {
    goToPosition(&(*placement).position);
    //reduce angle so that 0 <= rotation < 512
    //multiply by four to choose sprite
    //divide by 512 to get 0 <= rotationOffset < 4
    uint8_t rotationOffset = roundFix(((DIRECTIONS * ((*placement).rotation & 511)) << 14)/512);
    rotationOffset %= DIRECTIONS;
    drawSpriteTiles(&PLAYER[rotationOffset], 1, 1);
}

void undrawBullet(const placement_t *placement) {
    goToPosition(&(*placement).position);
    printf(" ");
}

void drawBullet(const placement_t *placement) {
    goToPosition(&(*placement).position);
    // TODO: Draw bullet with different character depending on where it is.
    // For example draw as "." if it's in the bottom of a character and as "\" if its in the top.
    drawSpriteTiles(&BULLET, 1, 1);
}
