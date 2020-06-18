#include <stdint.h>
#include "enemy.h"
#include "fix_point_math.h"
#include "movement.h"
#include "collision.h"


void fireBulletFromEnemy(enemy_t* enemy){
    if(!(*enemy).weaponCooldown){
        fireBulletFromPlacement((*enemy).placement);
        (*enemy).weaponCooldown = WEAPON_COOLDOWN;
    }
}


static void incrementPlayerPoints(player_t *players, uint8_t playerCount, enemy_t *enemy) {
    for (int i = 0; i < playerCount; i++){
        players[i].points += (*enemy).points;
    }
}


void enemyCollideBullet(player_t *players, uint8_t playerCount, enemy_t *enemy, bullet_t *bullet) {
    if (entitiesCollide((*enemy).placement, (*bullet).placement)) {
        incrementPlayerPoints(players, playerCount, enemy);
    }
}

void enemyCollidePlayer(enemy_t *enemy, player_t *player) {
    if (entitiesCollide((*player).placement, (*enemy).placement)) {
        (*player).points += (*enemy).points;
        //removeItem(enemy);
    }
}

void enemyCollideWall(level_t level, enemy_t *enemy) {
    if (entityCollidesWall(level, &(*enemy).placement)) {
        // *enemy.velocity = -enemy.velocity;
    }
}
