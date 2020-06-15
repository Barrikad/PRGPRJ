#ifndef ENTITY_REPRESENTATION_H_INCLUDED
#define ENTITY_REPRESENTATION_H_INCLUDED

typedef struct{
    vector_t position;
    vector_t radiusHV; // horizontal and vertical radius of entity.
    deg512 rotation;
}placement_t;

#endif /* ENTITY_REPRESENTATION_H_INCLUDED */
