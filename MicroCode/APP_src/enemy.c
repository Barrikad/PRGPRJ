#include <stdint.h>
#include "enemy.h"
#include "fix_point_math.h"
#include "movement.h"
#include "collision.h"


void initEnemy(enemy_t *enemy, vector_t position, deg512_t rotation) {
    // This is very verbose, but this is intentional, since it makes it easy to
    // see which values are set to what.
    (*enemy).placement.position = position;
    (*enemy).placement.hitboxWidth = createFix(1);
    (*enemy).placement.hitboxHeight = createFix(1);
    (*enemy).placement.rotation = rotation;
    (*enemy).lives = 5;
    (*enemy).points = 2;
    (*enemy).weaponCooldown = 0;
    (*enemy).checkpointIndex = 0;
}


void fireBulletFromEnemy(enemy_t* enemies, uint8_t index){
    if(!enemies[index].weaponCooldown){
        fireBulletFromPlacement(&enemies[index].placement,5);
        enemies[index].weaponCooldown = WEAPON_COOLDOWN;
    }
}


static void incrementPlayerPoints(player_t *players, uint8_t index, enemy_t *enemy) {
    players[index].points += (*enemy).points;
}


uint8_t enemyCollideBullet(player_t *players, enemy_t *enemy, bullet_t *bullet) {
    if (((*bullet).shotBy != 5) && entitiesCollide((*enemy).placement, (*bullet).placement)) {
        incrementPlayerPoints(players, (*bullet).shotBy - 1, enemy);
        (*enemy).lives -= 1;
        return 1;
    }
    return 0;
}
