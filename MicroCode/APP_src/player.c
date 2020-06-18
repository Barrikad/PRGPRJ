#include "player.h"
#include "bullet.h"
#include "game.h"

void initPlayer(player_t *player, vector_t position, deg512_t rotation, action_t (*inputFunction)()) {
    // This is very verbose, but this is intentional, since it makes it easy to
    // see which values are set to what.
    (*player).placement.position.x = position.x;
    (*player).placement.position.y = position.y;
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
        fireBulletFromPlacement((*player).placement);
        (*player).weaponCooldown = WEAPON_COOLDOWN;
    }
}

//add an angle to rotation, with modulo
static void rotateByAngle(deg512_t *rotation, deg512_t angle){
    *rotation += angle;
    *rotation &= 511;
}

//get input from all player input devices and realize the mapped actions
void processPlayerActionsInGame(player_t *player) {
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
        rotateByAngle(&(*player).placement.rotation,-8);
    }
    //player rotates right
    if(input & 4){
        rotateByAngle(&(*player).placement.rotation,8);
    }


    //rotate a vector of length 1 to the orientation of the player
    vector_t unitVector = {1 << 14,0};
    pRot = (*player).placement.rotation;
    rotateVector(&unitVector,pRot);


    //player moves forward
    if(input & 8){
        (*player).velocity.x = unitVector.x;
        (*player).velocity.y = unitVector.y;
    }
    //player moves backward
    else if(input & 16){
        (*player).velocity.x = -unitVector.x;
        (*player).velocity.y = -unitVector.y;
    }
    //player doesn't move
    else{
        (*player).velocity.x = 0;
        (*player).velocity.y = 0;
    }
}
