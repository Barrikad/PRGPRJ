#include "player.h"
#include "bullet.h"
#include "level.h"
#include "game_state.h"

void movePlayer(player_t *player){
    //adds velocity to position
    (*player).placement.position.x += (*player).velocity.x;
    (*player).placement.position.y += (*player).velocity.y;
    (*player).placement.position.x &= (LEVEL_WIDTH << 14) - 1;
    (*player).placement.position.y &= (LEVEL_HEIGHT << 14) - 1;
}

void fireBulletFromPlayer(player_t player){
    //make the placement of the bullet the same as the players, but with bullet hitbox
    vector_t position = player.placement.position;
    vector_t radiusHV = BULLET_RADIUS;
    deg512_t rotation = player.placement.rotation;
    placement_t bulletPlacement = {position,radiusHV,rotation};


    //set velocity to 1 in the direction the bullet is pointing
    vector_t bulletVelocity = {1 << 14,0};
    rotateVector(&bulletVelocity,player.placement.rotation);

    //create bullet specified above
    bullet_t bullet = {bulletPlacement,bulletVelocity};

    //move the bullet out of the player
    moveBullet(&bullet);

    addBullet(bullet);
}
