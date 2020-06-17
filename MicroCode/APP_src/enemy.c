#include <stdint.h>
#include "enemy.h"
#include "fix_point_math.h"
#include "movement.h"
#include "level.h"
#include "bullet.h"


void moveEnemy(enemy_t *enemy){
    moveEntity(&(*enemy).placement,(*enemy).velocity,horizontalBound(),verticalBound());
}

void fireBulletEnemy(enemy_t* enemy){
    if(!(*enemy).weaponCooldown){
        fireBulletFromPlacement((*enemy).placement);
        (*enemy).weaponCooldown = WEAPON_COOLDOWN;
    }
}
