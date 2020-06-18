#include "game.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "level.h"
#include "ansi.h"
#include "draw_game.h"
#include "player_actions.h"
#include <stdio.h>

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


//-----------ENEMIES----------------
void addEnemy(enemy_t enemy){
    if(enemyCount < MAX_ENEMIES){
        enemies[enemyCount] = enemy;
        enemyCount++;
    }
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


void processGameTick() {
    processPlayerActionsInGame();
    movePlayers();
    moveBullets();
    reduceWeaponCooldowns();

    // TODO: Move this into main collision detection
    playerCollideWall(&players[0]);

    renderLevel(firstLevel);

    cursorToXY(40, 0);
    printf("%i ", players[0].placement.rotation);

    drawGame(players, playerCount, bullets, bulletCount);
}
