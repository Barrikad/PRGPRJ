#include "game.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "level.h"
#include "ansi.h"
#include "graphics.h"
#include "enemy_AI.h"
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


void initLevel(level_t level) {
    renderLevel(level);
    vector_t position = {createFix(1), createFix(1)};
    addPlayer(position, 0, movementFromJoystick);
    // TODO: Store current level?
}


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

static void processPlayer(player_t *player) {
    uint8_t i;
    // Un-render bullet with the current position, so that we can simply draw it at the new position in the end
    undrawPlayer(&(*player).placement);

    processPlayerActionsInGame(player);

    // Player attributes
    movePlayer(player);
    if ((*player).weaponCooldown) {
        (*player).weaponCooldown--;
    }

    // Collision
    for (i = 0; i < bulletCount; i++) {
        playerCollideBullet(player, &bullets[i]);
    }
    playerCollideWall(firstLevel, player);
    // playerCollidePowerUp(player, powerUp);
    // playerCollideDoor(player, door);

    // Rendering
    drawPlayer(&(*player).placement);
}

static void processBullet(bullet_t *bullet) {
    // Un-render bullet with the current position, so that we can simply draw it at the new position in the end
    undrawBullet(&(*bullet).placement);

    moveBullet(bullet);

    // Collision
    bulletCollideWall(firstLevel, bullet);

    // Rendering
    drawBullet(&(*bullet).placement);
}

static void processEnemy(enemy_t *enemy) {
    uint8_t i;

    // Enemy attributes
    if ((*enemy).weaponCooldown) {
        (*enemy).weaponCooldown--;
    }

    // Collision
    for (i = 0; i < bulletCount; i++) {
        // TODO: Maybe add fromPlayer property on bullet, so we don't have to pass all players in here?
        enemyCollideBullet(players, playerCount, enemy, &bullets[i]);
    }
    for (i = 0; i < playerCount; i++) {
        enemyCollidePlayer(enemy, &players[i]);
    }
    enemyCollideWall(firstLevel, enemy);

    // TODO: More here!
}


void processGameTick() {
    //test code
    processEnemyActions(players,playerCount,enemies,enemyCount);
    //tset

    uint8_t i;
    // Process entities
    for (i = 0; i < playerCount; i++) {
        processPlayer(&players[i]);
    }
    for (i = 0; i < bulletCount; i++) {
        processBullet(&bullets[i]);
    }
    for (i = 0; i < enemyCount; i++) {
        processEnemy(&enemies[i]);
    }

    // Debug print current player rotation
    cursorToXY(40, 0);
    printf("%3i", players[0].placement.rotation);
}
