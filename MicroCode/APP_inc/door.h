#ifndef DOOR_H_INCLUDED
#define DOOR_H_INCLUDED

#include "entity_representation.h"
#include "level.h"

typedef struct{
    placement_t placement;
    level_t nextLevel;
} door_t;

void initDoor(door_t *door, vector_t position, level_t nextLevel);

#endif /* DOOR_H_INCLUDED */
