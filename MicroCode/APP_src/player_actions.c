#include <stdint.h>
#include "player.h"
#include "fix_point_math.h"
#include "movement.h"


typedef struct{
    player_t* player;
    action_t (*inputFun)();
}playerWithInput_t;

static uint8_t numberOfInputs = 0;
static playerWithInput_t playerWithInputs[4];


//register a player to be affected by an input function, f.x. joystick
void addPlayerWithInput(player_t* player, uint16_t (*inputFun)()){
    playerWithInputs[numberOfInputs].player = player;
    playerWithInputs[numberOfInputs].inputFun = inputFun;
    numberOfInputs++;
}

//add an angle to rotation, with modulo
static void rotateByAngle(deg512_t *rotation, deg512_t angle){
    *rotation += angle;
    *rotation &= 511;
}


//get input from all player input devices and realize the mapped actions
void processPlayerActionsInGame(){
    action_t input;
    deg512_t pRot;

    //for players in inputmapping
    for(int i = 0; i < numberOfInputs; i++){
        //get player input
        input = playerWithInputs[i].inputFun();

        //player shoots
        if(input & 1){
            fireBulletFromPlayer(playerWithInputs[i].player);
        }

        //player rotates left
        if(input & 2){
            rotateByAngle(&(*(playerWithInputs[i].player)).placement.rotation,-8);
        }
        //player rotates right
        if(input & 4){
            rotateByAngle(&(*(playerWithInputs[i].player)).placement.rotation,8);
        }


        //rotate a vector of length 1 to the orientation of the player
        vector_t unitVector = {1 << 14,0};
        pRot = (*(playerWithInputs[i].player)).placement.rotation;
        rotateVector(&unitVector,pRot);


        //player moves forward
        if(input & 8){
            (*(playerWithInputs[i].player)).velocity.x = unitVector.x;
            (*(playerWithInputs[i].player)).velocity.y = unitVector.y;
        }
        //player moves backward
        else if(input & 16){
            (*(playerWithInputs[i].player)).velocity.x = -unitVector.x;
            (*(playerWithInputs[i].player)).velocity.y = -unitVector.y;
        }
        //player doesn't move
        else{
            (*(playerWithInputs[i].player)).velocity.x = 0;
            (*(playerWithInputs[i].player)).velocity.y = 0;
        }
    }
}

