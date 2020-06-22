#include "game.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "powerUp.h"
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
static vector_t enemyCheckpoints[MAX_ENEMIES][CHECKPOINT_COUNT];

#define MAX_POWERUPS 8
//actual number of bullets in bulletCount
static uint8_t powerUpCount = 0;
static powerUp_t powerUps[MAX_POWERUPS];


// Purple
#define playerColor 5
// Yellow
#define enemyColor 11
// Red
#define bulletColor 1
// Cyan
#define powerUpColor 6


void initLevel(level_t level) {
    resetcolor();
    clrscr();
    // Render level with doors closed
    renderLevel(level, 0);
    vector_t position = {createFix(2), createFix(9)};
    addPlayer(position, 0, movementFromJoystick);

    // Test enemy behavior
    vector_t pos = {11 << 14, 6 << 14};
    deg512_t rot = 0;
    placement_t plc = {pos, 1 << 13, 1 << 13, rot};
    enemy_t enemy = {plc,0,0,0,0};
    addEnemy(enemy);
    vector_t cp1 = {11 << 14, 6 << 14};
    vector_t cp2 = {9 << 14, 3 << 14};
    enemyCheckpoints[0][0] = cp1;
    enemyCheckpoints[0][1] = cp2;
    enemyCheckpoints[0][2] = cp1;
    enemyCheckpoints[0][3] = cp2;
    enemyCheckpoints[0][4] = cp1;
    enemyCheckpoints[0][5] = cp2;
    enemyCheckpoints[0][6] = cp1;
    enemyCheckpoints[0][7] = cp2;

    // Test powerup
    vector_t puPos = {2 << 14,4 << 14};
    effects_t effect = 1;
    addPowerUp(puPos,effect);

    // TODO: Store current level?
}


void addPlayer(vector_t position, deg512_t rotation, action_t (*inputFunction)()) {
    if (playerCount >= MAX_PLAYERS) {
        return;
    }
    initPlayer(&players[playerCount], position, rotation, inputFunction);
    drawTank(&players[playerCount].placement, playerColor);
    playerCount++;
}

void addBullet(bullet_t bullet) {
    if (bulletCount >= MAX_BULLETS) {
        return;
    }
    bullets[bulletCount] = bullet;
    drawBullet(&bullets[bulletCount].placement, bulletColor);
    bulletCount++;
}

static void deleteBullet(uint8_t index) {
    bullet_t *thisBullet = &bullets[index];
    const bullet_t *lastBullet = &bullets[bulletCount - 1];
    (*thisBullet).placement = (*lastBullet).placement;
    (*thisBullet).velocity = (*lastBullet).velocity;
    bulletCount--;
}

void addEnemy(enemy_t enemy) {
    if (enemyCount >= MAX_ENEMIES) {
        return;
    }
    enemies[enemyCount] = enemy;
    drawTank(&enemies[enemyCount].placement, enemyColor);
    enemyCount++;
}

void addPowerUp(vector_t position, effects_t effect){
    if (powerUpCount >= MAX_POWERUPS){
        return;
    }
    placement_t plc = {position,POWERUP_WIDTH,POWERUP_HEIGHT,0};
    powerUp_t powerUp = {plc,effect};

    powerUps[powerUpCount] = powerUp;
    drawPowerUp(&powerUp.placement, powerUpColor);
    powerUpCount++;
}

void deletePowerUp(uint8_t index){
    undrawPowerUp(&powerUps[index].placement);

    powerUps[index].placement = powerUps[powerUpCount - 1].placement;
    powerUps[index].effects = powerUps[powerUpCount - 1].effects;
    powerUpCount--;
}

static void processPlayer(player_t *player) {
    uint8_t i;
    placement_t previousPlacement = (*player).placement;

    processPlayerActionsInGame(player);

    // Player attributes
    movePlayer(player);
    if ((*player).weaponCooldown) {
        (*player).weaponCooldown--;
    }

    // Collision walls
    for (i = 0; i < bulletCount; i++) {
        playerCollideBullet(player, &bullets[i]);
    }

    // Collision powerups
    for (i = 0; i < powerUpCount; i++) {
        playerCollidePowerUp(player, powerUps, i);
    }

    playerCollideWall(firstLevel, player);
    // playerCollidePowerUp(player, powerUp);
    // playerCollideDoor(player, door);

    // Render purple tank
    if (shouldRedraw(&previousPlacement, &(*player).placement)) {
        undrawTank(&previousPlacement);
        drawTank(&(*player).placement, playerColor);
    }
}

// Returns whether the bullet should be deleted
static uint8_t processBullet(bullet_t *bullet) {
    placement_t previousPlacement = (*bullet).placement;

    moveBullet(bullet);

    // Collision
    if (bulletCollideWallAndShouldDelete(firstLevel, bullet)) {
        undrawBullet(&previousPlacement);
        return 1;
    }

    // Rendering
    if (shouldRedraw(&previousPlacement, &(*bullet).placement)) {
        undrawBullet(&previousPlacement);
        drawBullet(&(*bullet).placement, bulletColor);
    }

    return 0;
}

static void processEnemy(enemy_t *enemy, vector_t *checkpoints) {
    uint8_t i;
    placement_t previousPlacement = (*enemy).placement;

    // Enemy attributes
    if ((*enemy).weaponCooldown) {
        (*enemy).weaponCooldown--;
    }

    //move and shoot
    processEnemyActions(players,playerCount,enemy, checkpoints);

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
    if (shouldRedraw(&previousPlacement, &(*enemy).placement)) {
        undrawTank(&previousPlacement);
        drawTank(&(*enemy).placement, enemyColor);
    }
}


void processGameTick() {

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
        processEnemy(&enemies[i], enemyCheckpoints[i]);
    }

    // Debug print current player rotation
    cursorToXY(40, 0);
    printf("%3i", players[0].placement.rotation);
}



