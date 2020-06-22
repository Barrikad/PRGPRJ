#include <stdint.h>
#include "enemy.h"
#include "fix_point_math.h"
#include "movement.h"
#include "collision.h"


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
}

void enemyCollidePlayer(enemy_t *enemy, player_t *player) {
    //noop
    //if (entitiesCollide((*player).placement, (*enemy).placement)) {
        //(*player).points += (*enemy).points;
        //removeItem(enemy);
    //}
}

void enemyCollideWall(level_t level, enemy_t *enemy) {
    if (entityCollidesWall(level, &(*enemy).placement)) {
        // *enemy.velocity = -enemy.velocity;
    }
}
