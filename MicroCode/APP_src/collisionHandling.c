
#include <stdint.h>
#include "30010_io.h"
#include "stm32f30x.h"
#include "fix_point_math.h"
#include "entity_representation.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "powerUp.h"
#include "door.h"
#include "collision.h"
#include "led.h"
#include "level.h"



/*
//NOTE: walls, player and powerup is to specific for the API.
//this should be a general collision processing engine, which
//we send entities to from APP
  Collision checks:
    Player -> wall, bullet, enemy, power-up, door (next lvl)
    Enemy -> wall, bullet, player
    Bullet -> player, wall, enemy
*/



/*
void removeItem(itemType){
    //Some function to remove bullet/enemy/power-up when they are hit
}
*/

static void incrementPlayerPoints(player_t *players, uint8_t playerCount, enemy_t *enemy) {
    for (int i = 0; i < playerCount; i++){
        players[i].points += (*enemy).points;
    }
}


/*
void bounceBullet(bullet_t *bullet){
    if (wallHitbox().x - bullet.position.x == 0) { //checks if the bullet hit wall in x direction
        *bullet.velocity.x -= bullet.velocity.x;
    }
    else if (wallHitbox().y - bullet.position.y == 0){ //checks if the bullet hit wall in y direction
        *bullet.velocity.y -= bullet.velocity.y;
    }
    *bullet.position = *bullet.position - 1; //Earlier bullet position, don't know how to get it
}
*/


void playerCollideBullet(player_t *player, bullet_t *bullet) {
    if (entitiesCollide((*player).placement, (*bullet).placement)) {
        setLed(LED_RED); // This should be on a timer
        (*player).lives -= 1;
        //removeItem(bullet);
        }
}

void playerCollideEnemy(player_t *player, enemy_t *enemy) {
    if (entitiesCollide((*player).placement, (*enemy).placement)) {
        (*player).points += (*enemy).points;
        //removeItem(enemy);
        }
}


void playerCollidePowerUp(player_t *player, powerUp_t *powerUp){
    if (entitiesCollide((*player).placement, (*powerUp).placement)) {
        (*player).effects = 1;
        //removeItem(PowerUp);
    }
}


void playerCollideWall(player_t *player) {
    if (entityCollidesWall(firstLevel, &(*player).placement)) {
        // Don't care about setting the velocity, since that's controlled elsewhere!
        // TODO: Let the player "snap" into place
        (*player).placement.position.x -= (*player).velocity.x;
        (*player).placement.position.y -= (*player).velocity.y;
    }
}



void playerCollideDoor(player_t *player, door_t *door){
    if (entitiesCollide((*player).placement, (*door).placement)) {
        (*player).points += (*door).points;
    }
}


void enemyCollideBullet(player_t *players, uint8_t playerCount, enemy_t *enemy, bullet_t *bullet) {
    if (entitiesCollide((*enemy).placement, (*bullet).placement)) {
        incrementPlayerPoints(players, playerCount, enemy);
    }
}


/*
void enemyCollideWall(enemy_t *enemy, wall_t wall) {
    if (entitiesCollide((*enemy).placement, wall.placement)) {
        // *enemy.velocity = -enemy.velocity;
    }
}


void bulletCollideWall(bullet_t *bullet, wall_t wall) {
    if (entitiesCollide((*bullet).placement, wall.placement)) {
        bounceBullet();
    }
}

*/


void processPlayerCollisions(player_t *players, uint8_t playerCount, enemy_t *enemies, uint8_t enemyCount, bullet_t *bullets, uint8_t bulletCount, door_t *door, powerUp_t *powerUp) {
    for(int i = 0; i < playerCount; i++){
        for (int j = 0; j < bulletCount; j++) {
            playerCollideBullet(&players[i], &bullets[j]);
        }
        for (int k = 0; k < enemyCount; k++) {
            playerCollideEnemy(&players[i], &enemies[i]);
        }
        playerCollidePowerUp(&players[i], powerUp);
        //playerCollideWall(player_t *player, wall_t wall);
        playerCollideDoor(&players[i], door);
    }
}

void processEnemyCollisions(player_t *players, uint8_t playerCount, enemy_t *enemies, uint8_t enemyCount, bullet_t *bullets, uint8_t bulletCount) {
    for (int j = 0; j < bulletCount; j++) {
        for (int k = 0; k < enemyCount; k++) {
            enemyCollideBullet(players, playerCount, &enemies[k], &bullets[j]);
        }
    // enemyCollideWall(enemy_t *enemy, wall_t wall);
    }
}

void processBulletCollisions(bullet_t *bullets, uint8_t bulletCount) {
    for (int j = 0; j < bulletCount; j++) {
        //bulletCollideWall(bullet_t bullet, wall_t wall);
    }
}
