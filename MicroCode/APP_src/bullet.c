#include "level.h"
#include "bullet.h"
#include "entity_representation.h"

const vector_t BULLET_RADIUS = {1 << 13, 1 << 13};

void moveBullet(bullet_t *bullet){
    moveEntity(&((*bullet).placement),(*bullet).velocity,horizontalBound(),verticalBound());
}
