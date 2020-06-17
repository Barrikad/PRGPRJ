#ifndef COLLISION_H_INCLUDED
#define COLLISION_H_INCLUDED
#include <stdint.h>
#include "entity_representation.h"


// Checks if two entities have overlapping hitboxes
uint8_t entitiesCollide(placement_t entity1, placement_t entity2);




#endif /* COLLISION_H_INCLUDED */
