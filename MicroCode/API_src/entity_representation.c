#include "entity_representation.h"

void moveEntity(placement_t* placement, vector_t velocity, vector_t boundH, vector_t boundV){
    //move entity
    (*placement).position.x += velocity.x;
    (*placement).position.y += velocity.y;

    //move back if border was crossed
    if((*placement).position.x < boundH.x || (*placement).position.x > boundH.y){
        (*placement).position.x -= velocity.x;
    }
    if((*placement).position.y < boundV.x || (*placement).position.y > boundV.y){
        (*placement).position.y -= velocity.y;
    }
}
