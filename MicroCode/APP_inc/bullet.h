#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED
#include "fix_point_math.h"
#include "entity_representation.h"


typedef struct{
    placement_t placement;
    vector_t velocity;
}bullet_t;

const vector_t BULLET_RADIUS;


void moveBullet(bullet_t *bullet);




#endif /* BULLET_H_INCLUDED */
