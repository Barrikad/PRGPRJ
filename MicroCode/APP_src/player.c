#include "player.h"
#include "bullet.h"
#include "game.h"


void movePlayer(player_t *player){
    moveEntity(&(*player).placement,(*player).velocity);
}


void fireBulletFromPlayer(player_t* player){
    if(!(*player).weaponCooldown){
        fireBulletFromPlacement((*player).placement);
        (*player).weaponCooldown = WEAPON_COOLDOWN;
    }
}
