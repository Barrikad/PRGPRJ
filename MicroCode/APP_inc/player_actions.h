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

// Get input from player input devices and realize the mapped actions
void processPlayerActionsInGame(player_t *player);



#endif /* ACTIONS_H_INCLUDED */
