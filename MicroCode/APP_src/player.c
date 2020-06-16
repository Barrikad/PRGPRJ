#include "player.h"
#include "bullet.h"
#include "level.h"
#include "game_state.h"

uint8_t shootflag = 0;

void movePlayer(player_t *player){
    //adds velocity to position
    (*player).placement.position.x += (*player).velocity.x;
    (*player).placement.position.y += (*player).velocity.y;
    (*player).placement.position.x &= (LEVEL_WIDTH << 14) - 1;
    (*player).placement.position.y &= (LEVEL_HEIGHT << 14) - 1;
}

void fireBulletFromPlayer(player_t player){
    shootflag = 1;
}
