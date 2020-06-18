#include "graphics.h"

//0-right, 1-down, 2-left, 3-up
const char PLAYER[] = {195,194,180,193};
const char BULLET[] = {111,111,111,111};
const char ENEMY[] = {204,203,185,202};

void drawSpriteTiles(const char tiles[], uint8_t height, uint8_t width){
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

static void undrawSprite11(const vector_t *position) {
    // Position of top left corner
    uint16_t cornerLeft = floorFix((*position).x);
    uint16_t cornerTop = floorFix((*position).y);

    cursorToXY(cornerLeft, cornerTop);

    printf(" ");
}

//draw 1x1 sprite
void drawSprite11(const char sprite[], const placement_t *placement) {
    //position of top left corner
    uint16_t cornerLeft = floorFix((*placement).position.x);
    uint16_t cornerTop = floorFix((*placement).position.y);

    cursorToXY(cornerLeft,cornerTop);

    //reduce angle so that 0 <= rotation < 512
    //multiply by four to choose sprite
    //divide by 512 to get 0 <= rotationOffset < 4
    uint8_t rotationOffset = roundFix(((4 * ((*placement).rotation & 511)) << 14)/512);
    rotationOffset %= 4;
    drawSpriteTiles(sprite + rotationOffset,1,1);
}

void undrawPlayer(const placement_t *placement) {
    undrawSprite11(&(*placement).position);
}

void drawPlayer(const placement_t *placement) {
    drawSprite11(PLAYER, placement);
}

void undrawBullet(const placement_t *placement) {
    undrawSprite11(&(*placement).position);
}

void drawBullet(const placement_t *placement) {
    drawSprite11(BULLET, placement);
}
