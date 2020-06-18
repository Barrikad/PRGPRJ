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

static void deleteBullet(uint8_t index) {
    bullet_t *thisBullet = &bullets[index];
    const bullet_t *lastBullet = &bullets[bulletCount - 1];
    copyBullet(thisBullet, lastBullet);
    thisBullet->placement = lastBullet->placement;
    thisBullet->velocity = lastBullet->velocity;
    bulletCount--;
}

void addEnemy(enemy_t enemy){
    if(enemyCount < MAX_ENEMIES){
        enemies[enemyCount] = enemy;
        enemyCount++;
    }
}

static void processPlayer(player_t *player) {
    uint8_t i;
    undrawTank(&(*player).placement);

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

    // Render purple tank
    drawTank(&(*player).placement, 5);
}

// Returns whether the bullet should be deleted
static uint8_t processBullet(bullet_t *bullet) {
    undrawBullet(&(*bullet).placement);

    moveBullet(bullet);

    // Collision
    if (bulletCollideWallAndShouldDelete(firstLevel, bullet)) {
        return 1;
    }

    // Rendering
    drawBullet(&(*bullet).placement, 1);

    return 0;
}

static void processEnemy(enemy_t *enemy) {
    uint8_t i;
    undrawTank(&(*enemy).placement);

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

    // Render yellow tank
    drawTank(&(*enemy).placement, 11);
}


void processGameTick() {
    //test code
    processEnemyActions(players,playerCount,enemies,enemyCount);
    //tset

    uint8_t i;
    // Process entities.
    // Each of these de-render each tick, so we can simply draw them at the new position in the end.
    for (i = 0; i < playerCount; i++) {
        processPlayer(&players[i]);
    }
    for (i = 0; i < bulletCount; i++) {
        if (processBullet(&bullets[i])) {
            // TODO: Fix this so it doesn't skip bullets
            deleteBullet(i);
        }
    }
    for (i = 0; i < enemyCount; i++) {
        processEnemy(&enemies[i]);
    }

    // Debug print current player rotation
    cursorToXY(40, 0);
    printf("%3i", players[0].placement.rotation);
}
