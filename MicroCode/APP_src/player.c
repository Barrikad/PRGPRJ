#include "player.h"
#include "bullet.h"
#include "level.h"
#include "game_state.h"


void movePlayer(player_t *player){
    moveEntity(&(*player).placement,(*player).velocity,horizontalBound(),verticalBound());
}


void fireBulletFromPlayer(player_t player){
    fireBulletFromPlacement(player.placement);
}
