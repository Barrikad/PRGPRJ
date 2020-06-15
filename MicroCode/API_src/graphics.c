#include "graphics.h"

//0-up, 1-right, 2-down, 3-left
const char PLAYER[] = {193,195,194,180};
const char BULLET[] = {250,250,250,250};

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

//draw 1x1 sprite
void drawSprite11(const char sprite[], placement_t placement){
    //position of top left corner
    uint16_t cornerLeft = floorFix(placement.position.x);
    uint16_t cornerTop = floorFix(placement.position.y);

    //divide by two since our tiles are rectangular
    cursorToXY(cornerLeft,cornerTop/2);

    //reduce angle so that 0 <= rotation < 512
    //multiply by four to choose sprite
    //divide by 512 to get 0 <= rotationOffset < 4
    uint8_t rotationOffset = (4 * (placement.rotation & 511))/512;
    drawSpriteTiles(sprite + rotationOffset,1,1);
}
