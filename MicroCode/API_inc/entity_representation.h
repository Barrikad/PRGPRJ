#ifndef ENTITY_REPRESENTATION_H_INCLUDED
#define ENTITY_REPRESENTATION_H_INCLUDED

#include "fix_point_math.h"

//a structure defining position, orientation and occupied space
typedef struct{
    vector_t position;
    fix2_14_t hitboxWidth;
    fix2_14_t hitboxHeight;
    deg512_t rotation;
}placement_t;

//change the placement of an entity, based upon a velocity, within height and width bounds
//  boundH - horizontal min and max, where x is min and y max
//  boundV - vertical min and max, where x is min and y max
void moveEntity(placement_t* placement, vector_t velocity);

#endif /* ENTITY_REPRESENTATION_H_INCLUDED */
