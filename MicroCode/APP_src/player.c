#include "player.h"
#include "bullet.h"
#include "game.h"
#include "collision.h"
#include "led.h"

void initPlayer(player_t *player, vector_t position, deg512_t rotation, action_t (*inputFunction)()) {
    // This is very verbose, but this is intentional, since it makes it easy to
    // see which values are set to what.
    (*player).placement.position = position;
    (*player).placement.hitboxWidth = createFix(1);
    (*player).placement.hitboxHeight = createFix(1);
    (*player).placement.rotation = rotation;
    (*player).velocity.x = 0;
    (*player).velocity.y = 0;
    (*player).lives = 0;
    (*player).points = 0;
    (*player).weaponCooldown = 0;
    (*player).effects = 0;
    (*player).inputFunction = inputFunction;
}


void movePlayer(player_t *player){
    moveEntity(&(*player).placement,(*player).velocity);
}


void fireBulletFromPlayer(player_t* player){
    if(!(*player).weaponCooldown){
        //power up makes cooldown shorter, and bullets faster
        if((*player).effects & 1){
            //double of standard velocity
            fireBulletFromPlacementWithVelocity(&(*player).placement,1 << 11);
            //half of standard cooldown
            (*player).weaponCooldown = WEAPON_COOLDOWN/2;
        }
        else{
            //fire bullet
            fireBulletFromPlacement(&(*player).placement);
            //set cooldown
            (*player).weaponCooldown = WEAPON_COOLDOWN;
        }
    }
}

//add an angle to rotation, with modulo
static void rotateByAngle(deg512_t *rotation, deg512_t angle){
    *rotation += angle;
    *rotation &= 511;
}

//movement as defined for tanks
static void processTankPlayer(player_t *player){
    action_t input;
    deg512_t pRot;

    //get player input
    input = (*player).inputFunction();

    //player shoots
    if(input & 1){
        fireBulletFromPlayer(player);
    }

    //player rotates left
    if(input & 2){
        rotateByAngle(&(*player).placement.rotation, -2);
    }
    //player rotates right
    if(input & 4){
        rotateByAngle(&(*player).placement.rotation, 2);
    }


    // Set velocity to 0.03125 in the direction the player is pointing
    // Note: The velocity should be smaller than the hitbox!
    vector_t velocity = {1 << 9, 0};
    pRot = (*player).placement.rotation;
    rotateVector(&velocity,pRot);

    //player moves forward
    if(input & 8){
        (*player).velocity.x = velocity.x;
        (*player).velocity.y = velocity.y;
    }
    //player moves backward
    else if(input & 16){
        (*player).velocity.x = -velocity.x;
        (*player).velocity.y = -velocity.y;
    }
    //player doesn't move
    else{
        (*player).velocity.x = 0;
        (*player).velocity.y = 0;
    }
}

//movement as defined for cycles
static void processMotorCyclePlayer(player_t *player){

    action_t input;
    deg512_t pRot;

    //get player input
    input = (*player).inputFunction();

    //motorcycle powerup makes player shoot continually
    fireBulletFromPlayer(player);

    //double rotating speed for motorcycle
    //player rotates left
    if(input & 2){
        rotateByAngle(&(*player).placement.rotation, -6);
    }
    //player rotates right
    if(input & 4){
        rotateByAngle(&(*player).placement.rotation, 6);
    }


    // double velocity for motorcycle
    // Set velocity to 0.03125*2 in the direction the player is pointing
    // Note: The velocity should be smaller than the hitbox!
    vector_t velocity = {1 << 10, 0};
    pRot = (*player).placement.rotation;
    rotateVector(&velocity,pRot);

    //forced forwards movement for motorcycle
    (*player).velocity.x = velocity.x;
    (*player).velocity.y = velocity.y;
}


//get input from all player input devices and realize the mapped actions
void processPlayerActionsInGame(player_t *player) {
    //bit 1 on means player is motorcycle
    if((*player).effects & 1){
        processMotorCyclePlayer(player);
    }
    //bit 1 off means player is tank
    else{
        processTankPlayer(player);
    }
}

/*
void removeItem(itemType){
    //Some function to remove bullet/enemy/power-up when they are hit
}
*/


void playerCollideBullet(player_t *player, bullet_t *bullet) {
    if (entitiesCollide((*player).placement, (*bullet).placement)) {
        setLed(LED_RED); // This should be on a timer
        (*player).lives -= 1;
        //removeItem(bullet);
    }
}


void playerCollidePowerUp(player_t *player, powerUp_t *powerUps, uint8_t index) {
    if (entitiesCollide((*player).placement, powerUps[index].placement)) {
        (*player).effects |= powerUps[index].effects;
        deletePowerUp(index);
    }
}


void playerCollideWall(level_t level, player_t *player) {
    placement_t *placement = &(*player).placement;
    levelCollision_t collision = entityCollidesWall(level, placement);
    // Don't care about setting the velocity, since that's controlled elsewhere!
    if (collision & collideTop) {
        (*placement).position.y = (floorFix((*placement).position.y) + 1) << FIX14_SHIFT;
    }
    if (collision & collideBottom) {
        (*placement).position.y = floorFix((*placement).position.y) << FIX14_SHIFT;
    }
    if (collision & collideLeft) {
        (*placement).position.x = (floorFix((*placement).position.x) + 1) << FIX14_SHIFT;
    }
    if (collision & collideRight) {
        (*placement).position.x = floorFix((*placement).position.x) << FIX14_SHIFT;
    }
}


void playerCollideDoor(player_t *player, const door_t *door) {
    if (entitiesCollide((*player).placement, (*door).placement)) {
        // (*player).points += (*door).points;
    }
}
