#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED
#include "fix_point_math.h"


typedef struct{
    vector_t position;
    vector_t velocity;
}bullet_t;


moveBullets(bullet_t *bullet);

setBulletVelocity(bullet_t *bullet, vector_t velocity);



#endif /* BULLET_H_INCLUDED */
