#include <stdint.h>
#include "30010_io.h"
#include "stm32f30x.h"
#include "fix_point_math.h"
#include "entity_representation.h"


// Private function
// Checks if the hitboxes are overlapping in one dimension.
static uint8_t hitboxesAreOverlapping(fix14_t distance, fix14_t radius1, fix14_t radius2){
    return distance - radius1 - radius2 < 0;
    // By knowing that all hitboxes are rectangles, it is possible to check
    // if the hitboxes are overlapping by looking at the distance between the
    // positions of the object, and size of the hitbox.
}

// Checks if two entities collide
// Parameters       entity1
//                  entity2
uint8_t entitiesCollide(placement_t entity1, placement_t entity2){
    fix14_t difference_x = entity1.position.x - entity2.position.x;
    fix14_t difference_y = entity1.position.y - entity2.position.y;

    if(difference_x < 0){
        difference_x = -difference_x;
    }

    if(difference_y < 0){
        difference_y = -difference_y;
    }

    uint8_t overlapX = hitboxesAreOverlapping(differnce_x,entity1.radiusHV.x, entity2.radiusHV.x);
    uint8_t overlapY = hitboxesAreOverlapping(diffence_y, entity1.radiusHV.y, entity2.radiusHV.y);

    return overlapX && overlapY;

    // Function takes two entities and sees if there is an overlap between the hitboxes of the enitities.
    // If there is an overlap the function returns 1, otherwise it returns 0.
}

