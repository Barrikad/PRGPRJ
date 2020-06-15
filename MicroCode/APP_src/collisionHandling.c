#include "<stdint.h>"
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
        *player.position = *player.position -1;  //Earlier player position
    }
}
*/

void playerCollideDoor(player_t *player, door_t door){
    if (entitiesCollide(player.placement, door.placement) {
        *player.points += door.points;
}


void enemyCollideBullet(enemy_t *enemy, bullet_t bullet) {
    if (entitiesCollide(enemy.placement, bullet.placement)
        player
}



void playerCollision(player_t player){
    player_t** players = allPlayers();
    uint8_t numOfPLayers = numberOfPlayers();
    for(i < numOfPLayers){
        for(i < numOf bullets){
            if collides:
                    dostuff
        }
    }
    if (entitiesCollide(player.placement)

            playerHitbox() == bulletHitbox()){
        setLed(LED_RED);
        *player.lives -= 1;
        //removeItem(Bullet);
    }
    else if (playerHitbox() == enemyHitbox()){ // If the player run the enemy down, the enemy dies.
        *player.points += enemy.points
        //removeItem(enemy);
    }
    if (playerHitbox() == powerupHitbox()){
        *player.effect = 1;
        //removeItem(powerup);
    }
    if (playerHitbox() == wallHitbox()){

    }
    if(playerHitbox() == doorHitbox()) {
        *player.points += 1000 //A reward for clearing lvl (Just an idea, doesn't need to be like this.)
        // Initiate new level design
    }
}

void enemyCollision() {
    if (enemyHitbox() == wallHitbox()){
    // *enemy.position = *enemy.position  - 1; //Earlier enemy position
    }
}

void bulletCollision() {
    if (bulletHitbox() == wallHitbox()) {
        bounceBullet();
    }
    if (bulletHitbox() == enemyHitbox()) {
        *player.points += enemy.points;
        // itemRemove(bullet);
        // itemRemove(enemy);
    }
}

void bounceBullet(bullet_t *bullet){
    if (wallHitbox().x - bullet.position.x == 0) { //checks if the bullet hit wall in x direction
        *bullet.velocity.x -= *bullet.velocity.x;
    }
    else if (wallHitbox().y - bullet.position.y == 0){ //checks if the bullet hit wall in y direction
        *bullet.velocity.y -= *bullet.velocity.y;
    }
    *bullet.position = *bullet.position - 1; //Earlier bullet position, don't know how to get it
}

void processCollisions() {
    playerCollision();
    enemyCollision();
    bulletCollision();
}

