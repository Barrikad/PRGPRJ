#include "player.h"
#include "bullet.h"
#include "game.h"

void initPlayer(player_t *player, vector_t position, deg512_t rotation) {
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
