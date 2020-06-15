/*
#include <stdint.h>
#include "30010_io.h"
#include "stm32f30x.h"
//NOTE: We should never include headers from APP in API
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "fix_point_math.h"
#include "entity_representation"

#define PLAYER_RADIUS 1
*/

//NOTE: walls, player and powerup is to specific for the API.
//this should be a general collision processing engine, which
//we send entities to from APP
/*  Collision checks:
    Player -> wall, bullet, enemy, power-up, door (next lvl)
    Enemy -> wall, bullet, player
    Bullet -> player, wall, enemy
*/

// This needs to be somewhere else, but is here for now
/*
vector_t powerupPosition;
*/

/*
uint8_t[] removeItem(itemType){
    //Some function to remove bullet/enemy/power-up when they are hit
} {2,4,3,5}
*/

/*
uint8_t entitiesCollide(placement_t entity1, placement_t entity2){
    if collides return 1
    return 0
}
*/

/*
void playerHitbox(player_t player){
    player.position;
    player.pos.x = 3
    player.pos.y = 4

}

void bulletHitbox(bullet_t bullet){
    bullet.position;
}

void enemyHitbox(enemy_t enemy){
    enemy.position;
}

void powerupHitbox(){
    powerupPosition;
}

void wallHitbox(){
    // Need some lvl creation coordinate to find out where the wall is.
}

void doorHitbox(){
    // Need some lvl creation coordinate to find out where the door is.
}

void playerCollision(){
    if (playerHitbox() == bulletHitbox()){
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
        // *player.position = *player.position -1;  //Earlier player position
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
*/
