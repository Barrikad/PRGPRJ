#include "player.h"
#include "bullet.h"
#include "enemy.h"

#define MAX_PLAYERS 4
//array of players, and size of actually contained players
static uint8_t playerCount = 0;
static player_t players[MAX_PLAYERS];

#define MAX_BULLETS 8
//actual number of bullets in bulletCount
static uint8_t bulletCount = 0;
static bullet_t bullets[MAX_BULLETS];

#define MAX_ENEMIES 16
//actual number of enemies in enemyCount
static uint8_t enemyCount = 0;
static enemy_t enemies[MAX_ENEMIES];


//--------------PLAYERS-----------
void addPlayer(player_t player){
    if(playerCount < MAX_PLAYERS){
        players[playerCount] = player;
        playerCount++;
    }
}

void movePlayers(){
    for(int i = 0; i < playerCount; i++){
        movePlayer(players + i);
    }
}

uint8_t numberOfPlayers(){
    return playerCount;
}

//only ever use this pointer for reading!
player_t* allPlayers(){
    return players;
}


//------------BULLETS-------------
void addBullet(bullet_t bullet){
    if(bulletCount < MAX_BULLETS){
        bullets[bulletCount] = bullet;
        bulletCount++;
    }
}

void moveBullets(){
    for(int i = 0; i < bulletCount; i++){
        moveBullet(bullets + i);
    }
}

uint8_t numberOfBullets(){
    return bulletCount;
}

//Only ever use this pointer for reading!
bullet_t* allBullets(){
    return bullets;
}


//-----------ENEMIES----------------
void addEnemy(enemy_t enemy){
    if(enemyCount < MAX_ENEMIES){
        enemies[enemyCount] = enemy;
        enemyCount++;
    }
}

void moveEnemies(){
    for(int i = 0; i < enemyCount; i++){
        moveEnemy(enemies + i);
    }
}

uint8_t numberOfEnemies(){
    return enemyCount;
}

enemy_t* allEnemies(){
    return enemies;
}

//--------------ALL-------------
void reduceWeaponCooldowns(){
    //players
    for(int i = 0; i < playerCount; i++){
        if(players[i].weaponCooldown)
            players[i].weaponCooldown--;
    }

    //enemies
    for(int i = 0; i < enemyCount; i++){
        if(enemies[i].weaponCooldown)
            enemies[i].weaponCooldown--;
    }
}
