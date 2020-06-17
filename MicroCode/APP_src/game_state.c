#include "player.h"
#include "bullet.h"
#include "enemy.h"

#define MAX_PLAYERS 4
//array of players, and size of actually contained players
static uint8_t playerCount = 0;
static player_t players[MAX_PLAYERS];

#define MAX_BULLETS 8
//actual number of bullets in bulletCount
static uint16_t bulletCount = 0;
static bullet_t bullets[MAX_BULLETS];

#define MAX_ENEMIES 16
//actual number of enemies in enemyCount
static uint8_t enemyCount = 0;
static enemy_t enemies[MAX_ENEMIES];


//--------------PLAYERS-----------
void addPlayer(player_t player){
    players[playerCount] = player;
    playerCount++;
}

void movePlayers(){
    for(int i = 0; i < playerCount; i++){
        movePlayer(players + i);
    }
}

uint8_t numberOfPlayers(){
    return playerCount;
}

//bad abstraction
player_t* allPlayers(){
    return players;
}


//------------BULLETS-------------
void addBullet(bullet_t bullet){
    bullets[bulletCount] = bullet;
    bulletCount++;
}

void moveBullets(){
    for(int i = 0; i < bulletCount; i++){
        moveBullet(bullets + i);
    }
}

uint8_t numberOfBullets(){
    return bulletCount;
}

//bad abstraction
bullet_t* allBullets(){
    return bullets;
}


//-----------ENEMIES----------------
void addEnemy(enemy_t enemy){
    enemies[enemyCount] = enemy;
    enemyCount++;
}

void moveEnemies(){
    for(int i = 0; i < enemyCount; i++){
        moveEnemy(enemies + i);
    }
}

uint8_t numberOfEnemies(){
    return enemyCount;
}

//bad abstraction. should probably be removed
enemy_t* allEnemies(){
    return enemies;
}

