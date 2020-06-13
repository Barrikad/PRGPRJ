#include "player.h"

void movePlayer(player_t *player){
    //adds velocity to position
    (*player).position.x += (*player).velocity.x;
    (*player).position.x += (*player).velocity.x;
}

void setPlayerVelocity(player_t *player, vector_t velocity){
    (*player).velocity = velocity;
}

void damagePlayer(player_t *player, uint8_t damage){
    (*player).lives -= damage;
}
