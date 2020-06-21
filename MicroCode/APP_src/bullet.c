#include "bullet.h"
#include "entity_representation.h"
#include "game.h"
#include "collision.h"

void moveBullet(bullet_t *bullet){
    //extract movement info from bullet and send to API
    moveEntity(&((*bullet).placement),(*bullet).velocity);
}

void fireBulletFromPlacement(const placement_t *placement){
    //make the placement of the bullet the same as the given placement, but with bullet hitbox
    vector_t position = {(*placement).position.x + (*placement).hitboxWidth / 2, (*placement).position.y + (*placement).hitboxHeight / 2};
    deg512_t rotation = (*placement).rotation;
    // Hitbox is 0.25 by 0.25
    placement_t bulletPlacement = {position, 1 << 12, 1 << 12, rotation};

    // Set velocity to 0.0625 in the direction the bullet is pointing
    // Note: The velocoty should be smaller than the hitbox!
    vector_t bulletVelocity = {1 << 10, 0};
    rotateVector(&bulletVelocity,rotation);

    //create bullet specified above
    bullet_t bullet = {bulletPlacement,bulletVelocity};

    //move the bullet out of the entity
    // Done a few times since the velocity is too low to do this the first time
    // TODO: Do this better!
    moveBullet(&bullet);
    moveBullet(&bullet);
    moveBullet(&bullet);
    moveBullet(&bullet);
    moveBullet(&bullet);

    addBullet(bullet);
}


/*
static void bounceBullet(bullet_t *bullet){
    if (wallHitbox().x - bullet.position.x == 0) { //checks if the bullet hit wall in x direction
        *(bullet).velocity.x -= bullet.velocity.x;
    }
    else if (wallHitbox().y - bullet.position.y == 0){ //checks if the bullet hit wall in y direction
        *(bullet).velocity.y -= bullet.velocity.y;
    }
    *(bullet).position = *bullet.position - 1; //Earlier bullet position, don't know how to get it
}
*/


uint8_t bulletCollideWallAndShouldDelete(level_t level, bullet_t *bullet) {
    if (entityCollidesWall(level, &(*bullet).placement)) {
        // TODO: Implement bullet bouncing X times off the wall.
        // bounceBullet();
        return 1;
    }
    return 0;
}

