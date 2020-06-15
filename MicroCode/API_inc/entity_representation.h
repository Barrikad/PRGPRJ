#ifndef ENTITY_REPRESENTATION_H_INCLUDED
#define ENTITY_REPRESENTATION_H_INCLUDED

#include "fix_point_math.h"

typedef struct{
    vector_t position;
    vector_t hitBox;
    deg512_t rotation;
}placement_t;

#endif /* ENTITY_REPRESENTATION_H_INCLUDED */
