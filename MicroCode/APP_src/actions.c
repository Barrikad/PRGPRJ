#include <stdint.h>
#include "player.h"
#include "fix_point_math.h"


typedef struct{
    player_t* player;
    uint16_t (*inputFun)();
}playerWithInput_t;

static uint8_t numberOfInputs = 0;
static playerWithInput_t playerWithInputs[4];


//register a player to be affected by an input function, f.x. joystick
void addPlayerWithInput(player_t* player, uint16_t (*inputFun)()){
    playerWithInputs[numberOfInputs].player = player;
    playerWithInputs[numberOfInputs].inputFun = inputFun;
    numberOfInputs++;
}


//get input from all player input devices and realize the mapped actions
void processPlayerActionsInGame(){
    for(int i = 0; i < numberOfInputs; i++){
        uint16_t input = playerWithInputs[i].inputFun();

        //player shoots
        if(input & 1){

        }

        //player rotates left
        if(input & 2){
            (*(playerWithInputs[i].player)).placement.rotation -= 32;
            (*(playerWithInputs[i].player)).placement.rotation &= 511;
        }

        //player rotates right
        if(input & 4){
            (*(playerWithInputs[i].player)).placement.rotation += 32;
            (*(playerWithInputs[i].player)).placement.rotation &= 511;
        }

        //rotate a vector of length 1 to the orientation of the player
        vector_t unitVector = {1 << 14,0};
        deg512_t pRot = (*(playerWithInputs[i].player)).placement.rotation;
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

