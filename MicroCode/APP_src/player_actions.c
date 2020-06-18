#include <stdint.h>
#include "player_actions.h"
#include "player.h"
#include "fix_point_math.h"
#include "movement.h"

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
    input = player.inputFun();

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

