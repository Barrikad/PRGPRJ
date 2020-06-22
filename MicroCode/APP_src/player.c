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
    (*player).lives = 99;
    (*player).points = 0;
    (*player).weaponCooldown = 0;
    (*player).effects = 0;
    (*player).inputFunction = inputFunction;
}


void movePlayer(player_t *player){
    moveEntity(&(*player).placement,(*player).velocity);
}


void fireBulletFromPlayer(player_t* players, uint8_t index){
    if(!players[index].weaponCooldown){
        //power up makes cooldown shorter, and bullets faster
        if(players[index].effects & 1){
            //double of standard velocity
            fireBulletFromPlacementWithVelocity(&players[index].placement,1 << 11,index + 1);
            //half of standard cooldown
            players[index].weaponCooldown = WEAPON_COOLDOWN/2;
        }
        else{
            //fire bullet from player
            fireBulletFromPlacement(&players[index].placement,index + 1);
            //set cooldown
            players[index].weaponCooldown = WEAPON_COOLDOWN;
        }
    }
}

//add an angle to rotation, with modulo
static void rotateByAngle(deg512_t *rotation, deg512_t angle){
    *rotation += angle;
    *rotation &= 511;
}

static void driftMove(player_t *player, vector_t acceleration){
    //velocity might become larger than max if acc and vel have same sign
    //if they have the same sign, vel after acc must be smaller than
    // 1
    if(((acceleration.x < 0 && (*player).velocity.x < 0)
        || (acceleration.x > 0 && (*player).velocity.x > 0))
          && absFix(acceleration.x + (*player).velocity.x) >= (1 << 12)){
        //set speed to almost max
        (*player).velocity.x = 1 << 12;
    }
    //acceleration is safe if acc and vel have different signs, or magnitude is still small
    else{
        (*player).velocity.x += acceleration.x;
    }

    //velocity might become larger than max if acc and vel have same sign
    if(((acceleration.y < 0 && (*player).velocity.y < 0)
        || (acceleration.y > 0 && (*player).velocity.y > 0))
          && absFix(acceleration.y + (*player).velocity.y) >= (1 << 12)){
        //set speed to almost max
        (*player).velocity.y = 1 << 12;
    }
    //acceleration is safe if acc and vel have different signs, or magnitude is still small
    else{
        (*player).velocity.y += acceleration.y;
    }
}


//movement as defined for tanks
static void processTankPlayer(player_t *players, uint8_t index){
    action_t input;
    deg512_t pRot;

    //get player input
    input = players[index].inputFunction();

    //player shoots
    if(input & 1){
        fireBulletFromPlayer(players, index);
    }

    //player rotates left
    if(input & 2){
        rotateByAngle(&players[index].placement.rotation, -2);
    }
    //player rotates right
    if(input & 4){
        rotateByAngle(&players[index].placement.rotation, 2);
    }


    // Set velocity to 0.03125 in the direction the player is pointing
    // Note: The velocity should be smaller than the hitbox!
    // much smaller velocity when drift mode is on
    vector_t velocity = {players[index].effects & 2 ? 1 << 4 :1 << 9, 0};
    pRot = players[index].placement.rotation;
    rotateVector(&velocity,pRot);

    //normal move if driftmode is off
    if(!(players[index].effects & 2)){
        //player moves forward
        if(input & 8){
            players[index].velocity.x = velocity.x;
            players[index].velocity.y = velocity.y;
        }
        //player moves backward
        else if(input & 16){
            players[index].velocity.x = -velocity.x;
            players[index].velocity.y = -velocity.y;
        }
        //player doesn't move
        else{
            players[index].velocity.x = 0;
            players[index].velocity.y = 0;
        }
    }
    else{
        //player moves forward
        if(input & 8){
            driftMove(players + index, velocity);
        }
        //player moves backward
        else if(input & 16){
            velocity.x = -velocity.x;
            velocity.y = -velocity.y;
            driftMove(players + index, velocity);
        }
        //player doesn't move
        else{
            velocity.x = 0;
            velocity.y = 0;
            driftMove(players + index, velocity);
        }
    }
}

//movement as defined for cycles
static void processMotorCyclePlayer(player_t *players, uint8_t index){

    action_t input;
    deg512_t pRot;

    //get player input
    input = players[index].inputFunction();

    //motorcycle powerup makes player shoot continually
    fireBulletFromPlayer(players,index);

    //double rotating speed for motorcycle
    //player rotates left
    if(input & 2){
        rotateByAngle(&players[index].placement.rotation, -6);
    }
    //player rotates right
    if(input & 4){
        rotateByAngle(&players[index].placement.rotation, 6);
    }


    // double velocity for motorcycle
    // Set velocity to 0.03125*2 in the direction the player is pointing
    // Note: The velocity should be smaller than the hitbox!
    // much slower velocity when drifting
    vector_t velocity = {players[index].effects & 2 ? 7 << 2 : 1 << 10, 0};
    pRot = players[index].placement.rotation;
    rotateVector(&velocity,pRot);

    //if not drift mode
    if(!(players[index].effects & 2)){
        //forced forwards movement for motorcycle
        players[index].velocity.x = velocity.x;
        players[index].velocity.y = velocity.y;
    }
    //if drift mode
    else{
        driftMove(players + index, velocity);
    }
}


//get input from all player input devices and realize the mapped actions
void processPlayerActionsInGame(player_t *players, uint8_t index) {
    //bit 1 on means player is motorcycle
    if(players[index].effects & 1){
        processMotorCyclePlayer(players,index);
    }
    //bit 1 off means player is tank
    else{
        processTankPlayer(players,index);
    }
}

/*
void removeItem(itemType){
    //Some function to remove bullet/enemy/power-up when they are hit
}
*/


uint8_t playerCollideBullet(player_t *players, uint8_t pIndex, bullet_t *bullet) {
    if (((*bullet).shotBy != pIndex + 1) && entitiesCollide(players[pIndex].placement, (*bullet).placement)) {
        setLed(LED_RED); // This should be on a timer
        players[pIndex].lives -= 1;
        return 1;
    }
    return 0;
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

    if (collision & collideTop) {
        (*placement).position.y = (floorFix((*placement).position.y) + 1) << FIX14_SHIFT;
        (*player).velocity.y = 0;
    }
    if (collision & collideBottom) {
        (*placement).position.y = floorFix((*placement).position.y) << FIX14_SHIFT;
        (*player).velocity.y = 0;
    }
    if (collision & collideLeft) {
        (*placement).position.x = (floorFix((*placement).position.x) + 1) << FIX14_SHIFT;
        (*player).velocity.x = 0;
    }
    if (collision & collideRight) {
        (*placement).position.x = floorFix((*placement).position.x) << FIX14_SHIFT;
        (*player).velocity.x = 0;
    }
}

