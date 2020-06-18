#include "entity_representation.h"

void moveEntity(placement_t* placement, vector_t velocity) {
    //move entity
    (*placement).position.x += velocity.x;
    (*placement).position.y += velocity.y;
}
