#ifndef ACTIONS_H_INCLUDED
#define ACTIONS_H_INCLUDED
#include "player.h"
#include "enemy.h"
#include "movement.h"

//notes on the goals of the architecture:
//  arbitrary number of players with arbitrary input devices
//  arbitrary number of enemies with arbitrary input devices
//  can have one function for each menu-like feature, but input should
//    be arbitrary
//this is extra important as we have not really yet decided on a final input method (13/06)

//notes to self
//  need uniform function signature for input devices from API


//register a player to be affected by an input function, f.x. joystick
void addPlayerWithInput(player_t* player, uint16_t (*inputFun)());

//register an enemy to be affected by an input function.
//This function might have to be aware of the enemy to calculate a decision
void addEnemyWithInput(enemy_t* enemy, uint16_t (*inputFun)(enemy_t enemy));

//get input from all player input devices and realize the mapped actions
void processPlayerActionsInGame();

//get input from all enemy input functions and realize the mapped actions
void processEnemyActionsInGame();



/*
Example script on how to use these functions

Assume the following functions exists in api:
uint16_t movementFromJoystick(); //bit 5 if is shooting, 4 if forward ...
uint16_t movementFromKeyboard();

Assume the following function exist in app:
uint16_t enemysBestMove(enemy_t *enemy); //has access to gamestate
                                         //identifies which enemy it is considering
                                         //uses some algorithm to decide input
                                         //bit 5 if is shooting, 4 if forward ...

We can then define functions like this in actions.c
void processPlayerActionsInGame(){
    for(player,input in players,inputs):
        inputValue = (*input)();
        if inputValue & 1:
            (*player).velocity.y += 1;
        ...
        ...
}


And in main we just initialize the inputs before the game:
addPlayerWithInput(&player1,movementFromJoystick);
addEnemyWithInput(&enemy1,enemysBestMove);
...
...

The input can even be decided while the game is running,
so it would be possible to choose through the menu

*/


#endif /* ACTIONS_H_INCLUDED */
