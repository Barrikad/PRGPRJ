#include <stdint.h>
#include "30010_io.h"
#include "stm32f30x.h"
#include "fix_point_math.h"
#include "player.h"
#include "enemy.h"
#include "bullet"
#include "powerUp.h"
#include "door.h"
#include "collision.h"
#include "led.h"




//NOTE: walls, player and powerup is to specific for the API.
//this should be a general collision processing engine, which
//we send entities to from APP
/*  Collision checks:
    Player -> wall, bullet, enemy, power-up, door (next lvl)
    Enemy -> wall, bullet, player
    Bullet -> player, wall, enemy
*/



/*
void removeItem(itemType){
    //Some function to remove bullet/enemy/power-up when they are hit
}
*/

static void incrementPlayerPoints(){
    uint8_t ps = numberOfPlayers();
    player_t** players = allPlayers();
    for(int i = 0; i < ps; i++){
        (*players[i]).points += enemy.points
    }
}

void bounceBullet(bullet_t *bullet){
    if (wallHitbox().x - bullet.position.x == 0) { //checks if the bullet hit wall in x direction
        *bullet.velocity.x -= bullet.velocity.x;
    }
    else if (wallHitbox().y - bullet.position.y == 0){ //checks if the bullet hit wall in y direction
        *bullet.velocity.y -= bullet.velocity.y;
    }
    *bullet.position = *bullet.position - 1; //Earlier bullet position, don't know how to get it
}

void playerCollideBullet(player_t *player, bullet_t bullet) {
    if (entitiesCollide(player.placement, bullet.placement) {
        setLed(LED_RED); // Dette skal være på en timer
        *player.lives -= 1;
        //removeItem(bullet);
        }
}

void playerCollideEnemy(player_t *player, enemy_t enemy) {
    if (entitiesCollide(player.placement, enemy.placement) {
        *player.points += enemy.points;
        //removeItem(enemy);
        }
}


void playerCollidePowerUp(player_t *player, powerUp_t powerUp){
    if (entitiesCollide(player.placement, powerUp.placement) {
        *player.effects = 1;
        //removeItem(PowerUp);
    }
}

/*
void playerCollideWall(player_t *player, wall_t wall) {
    if (entitiesCollide(player.placement, wall.placement) {
        *player.velocity = -player.velocity
    }
}
*/

void playerCollideDoor(player_t *player, door_t door){
    if (entitiesCollide(player.placement, door.placement) {
        *player.points += door.points;
    }
}




void enemyCollideBullet(enemy_t *enemy, bullet_t bullet) {
    if (entitiesCollide(enemy.placement, bullet.placement) {
        incrementPlayerPoints();
    }
}

/*
void enemyCollideWall(enemy_t *enemy, wall_t wall) {
    if (entitiesCollide(enemy.placement, wall.placement) {
        // *enemy.velocity = -enemy.velocity;
    }
}


void bulletCollideWall(bullet_t bullet, wall_t wall) {
    if (entitiesCollide(bullet.placement, wall.placement)) {
        bounceBullet();
    }
}

*/

void playerCollision() {
    playerCollideBullet(player_t *player, bullet_t bullet);
    playerCollideEnemy(player_t *player, enemy_t enemy);
    playerCollidePowerUp(player_t *player, powerUp_t powerUp);
    //playerCollideWall(player_t *player, wall_t wall);
    playerCollideDoor(player_t *player, door_t door);
}

void enemyCollision(){
    enemyCollideBullet(enemy_t *enemy, bullet_t bullet);
    // enemyCollideWall(enemy_t *enemy, wall_t wall);
}

void bulletCollision() {
    //bulletCollideWall(bullet_t bullet, wall_t wall);
}

void processCollisions() {
    playerCollision();
    enemyCollision();
    bulletCollision();
}

