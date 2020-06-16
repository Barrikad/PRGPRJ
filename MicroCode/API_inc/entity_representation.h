#ifndef ENTITY_REPRESENTATION_H_INCLUDED
#define ENTITY_REPRESENTATION_H_INCLUDED

#include "fix_point_math.h"

//a structure defining position, orientation and occupied space
typedef struct{
    vector_t position;
    vector_t radiusHV; // horizontal and vertical radius of entity.
    deg512_t rotation;
}placement_t;

//change the placement of an entity, based upon a velocity, within height and width bounds
//  boundH - horizontal min and max, where x is min and y max
//  boundV - vertical min and max, where x is min and y max
void moveEntity(placement_t* placement, vector_t velocity, vector_t boundH, vector_t boundV);

#endif /* ENTITY_REPRESENTATION_H_INCLUDED */
