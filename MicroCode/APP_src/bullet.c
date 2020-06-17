#include "bullet.h"
#include "entity_representation.h"
#include "game.h"

void moveBullet(bullet_t *bullet){
    //extract movement info from bullet and send to API
    moveEntity(&((*bullet).placement),(*bullet).velocity);
}

void fireBulletFromPlacement(placement_t placement){
    //make the placement of the bullet the same as the given placement, but with bullet hitbox
    vector_t position = placement.position;
    deg512_t rotation = placement.rotation;
    placement_t bulletPlacement = {position, createFix(1), createFix(1), rotation};


    //set velocity to 1 in the direction the bullet is pointing
    vector_t bulletVelocity = {BULLET_SPEED << 14,0};
    rotateVector(&bulletVelocity,rotation);

    //create bullet specified above
    bullet_t bullet = {bulletPlacement,bulletVelocity};

    //move the bullet out of the entity
    moveBullet(&bullet);

    addBullet(bullet);
}
