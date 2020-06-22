#include "door.h"
#include "collision.h"

void initDoor(door_t *door, vector_t position, level_t nextLevel) {
    (*door).placement.position = position;
    (*door).placement.hitboxWidth = createFix(1);
    (*door).placement.hitboxHeight = createFix(1);
    (*door).placement.rotation = 0;
    (*door).nextLevel = nextLevel;
}
