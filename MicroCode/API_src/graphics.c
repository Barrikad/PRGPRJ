#include "graphics.h"

//0-up, 1-right, 2-down, 3-left
const char player[] = {193,195,194,180};
const char bullet[] = {250,250,250,250};

//draw 1x1 sprite
void drawSprite11(char sprite[], vector_t position, deg512_t rotation){
    //position of top left corner
    uint16_t cornerLeft = floorFix(position.x);
    uint16_t cornerTop = floorFix(position.y);

    gotoxy(cornerLeft,cornerTop);



}
