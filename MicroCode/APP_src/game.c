#include "game.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "level.h"
#include "ansi.h"
#include "graphics.h"
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


void addPlayer(vector_t position, deg512_t rotation, action_t (*inputFunction)()) {
    if (playerCount >= MAX_PLAYERS) {
        return;
    }
    initPlayer(&players[playerCount], position, rotation, inputFunction);
    playerCount++;
}

void addBullet(bullet_t bullet){
    if(bulletCount < MAX_BULLETS){
        bullets[bulletCount] = bullet;
        bulletCount++;
    }
}

void addEnemy(enemy_t enemy){
    if(enemyCount < MAX_ENEMIES){
        enemies[enemyCount] = enemy;
        enemyCount++;
    }
}


void processGameTick() {
    uint8_t i;
    processPlayerActionsInGame(&players[0]);

    for (i = 0; i < playerCount; i++) {
        movePlayer(&players[i]);
    }

    for (i = 0; i < bulletCount; i++) {
        moveBullet(&bullets[i]);
    }

    for (i = 0; i < playerCount; i++) {
        if (players[i].weaponCooldown) {
            players[i].weaponCooldown--;
        }
    }

    for (i = 0; i < enemyCount; i++) {
        if (enemies[i].weaponCooldown) {
            enemies[i].weaponCooldown--;
        }
    }

    // TODO: Move this into main collision detection
    playerCollideWall(&players[0]);

    renderLevel(firstLevel);

    cursorToXY(40, 0);
    printf("%i ", players[0].placement.rotation);

    for(i = 0; i < playerCount; i++) {
        drawPlayer(&players[i].placement);
    }

    for(i = 0; i < bulletCount; i++){
        drawBullet(&bullets[i].placement);
    }
}
