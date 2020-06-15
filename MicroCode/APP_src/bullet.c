#include "level.h"
#include "bullet.h"

const vector_t BULLET_RADIUS = {1 << 13, 1 << 13};

void moveBullet(bullet_t *bullet){
    (*bullet).placement.position.x += (*bullet).velocity.x;
    (*bullet).placement.position.y += (*bullet).velocity.y;
    (*bullet).placement.position.x &= (LEVEL_WIDTH << 14) - 1;
    (*bullet).placement.position.y &= (LEVEL_HEIGHT << 14) - 1;
}
