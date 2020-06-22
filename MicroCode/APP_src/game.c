#include "game.h"
#include "player.h"
#include "door.h"
#include "bullet.h"
#include "enemy.h"
#include "powerUp.h"
#include "level.h"
#include "ansi.h"
#include "graphics.h"
#include "enemy_AI.h"
#include "collision.h"
#include "door.h"
#include "frame_timer.h"
#include <stdio.h>
#include "player_stat_graphics.h"

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

#define MAX_DOORS 4
static uint8_t doorCount = 0;
static door_t doors[MAX_DOORS];


static uint8_t isDoorsOpen;


// Purple
#define playerColor 5
// Yellow
#define enemyColor 11
// Light blue
#define powerUpColor 12
// Cyan, same as level walls
#define doorColor 6

//green,white,brown,blue,red
static const uint8_t bulletColors[] = {2,15,3,4,1};


static void addDoor(vector_t position, level_t nextLevel) {
    if (doorCount >= MAX_DOORS) {
        return;
    }
    initDoor(&doors[doorCount], position, nextLevel);
    // Draw the door as closed initially.
    drawDoor(&doors[doorCount].placement, doorColor, 0);
    doorCount++;
}


static void initLevel1() {
    vector_t position = {createFix(2), createFix(9)};
    addPlayer(position, 0, movementFromJoystick);

    // Test enemy behavior
    vector_t pos = {11 << 14, 6 << 14};
    deg512_t rot = 0;
    placement_t plc = {pos, 1 << 13, 1 << 13, rot};
    enemy_t enemy = {plc,0,0,2,0};
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
    players[0].effects |= 2;

    vector_t doorPosition1 = {createFix(13), createFix(2)};
    addDoor(doorPosition1, secondLevel);
    vector_t doorPosition2 = {createFix(13), createFix(3)};
    addDoor(doorPosition2, secondLevel);
}


static void initLevel2() {
    // TODO: Fix the positions of stuff in here!
    vector_t position = {createFix(2), createFix(9)};
    addPlayer(position, 0, movementFromJoystick);

    // Test enemy behavior
    vector_t pos = {11 << 14, 2 << 14};
    deg512_t rot = 0;
    placement_t plc = {pos, 1 << 13, 1 << 13, rot};
    enemy_t enemy = {plc,0,0,0,0};
    addEnemy(enemy);
    vector_t cp1 = {11 << 14, 2 << 14};
    vector_t cp2 = {11 << 14, 10 << 14};
    vector_t cp3 = {2 << 14, 10 << 14};
    vector_t cp4 = {2 << 14, 2 << 14};
    enemyCheckpoints[0][0] = cp1;
    enemyCheckpoints[0][1] = cp2;
    enemyCheckpoints[0][2] = cp3;
    enemyCheckpoints[0][3] = cp4;
    enemyCheckpoints[0][4] = cp1;
    enemyCheckpoints[0][5] = cp2;
    enemyCheckpoints[0][6] = cp3;
    enemyCheckpoints[0][7] = cp4;

    // Test powerup
    vector_t puPos = {11 << 14, 6 << 14};
    effects_t effect = 1;
    addPowerUp(puPos,effect);

    vector_t doorPosition1 = {createFix(0), createFix(2)};
    addDoor(doorPosition1, firstLevel);
    vector_t doorPosition2 = {createFix(0), createFix(3)};
    addDoor(doorPosition2, firstLevel);

    // TODO: Make doors that lead to the third level
}


void initLevel(level_t level) {
    // Clear screen and hide cursor
    cursorHide();
    resetcolor();
    clrscr();

    // Render level with doors closed
    renderLevel(level);
    isDoorsOpen = 0;

    switch(level) {
    case firstLevel:
        initLevel1();
        initFrameTimer(100);
        break;
    case secondLevel:
        initLevel2();
        initFrameTimer(150);
        break;
    default:
        // Unreachable
        break;
    }

    // Initializes score and lives screen.
    livesAndScoreLcd(players, playerCount);
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
    drawBullet(&bullets[bulletCount].placement, bulletColors[bullets[bulletCount].shotBy-1]);
    bulletCount++;
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
    drawPowerUp(&powerUp.placement, powerUpColor, effect & 2);
    powerUpCount++;
}

void deletePowerUp(uint8_t index){
    undrawPowerUp(&powerUps[index].placement);

    powerUps[index].placement = powerUps[powerUpCount - 1].placement;
    powerUps[index].effects = powerUps[powerUpCount - 1].effects;
    powerUpCount--;
}

static void renderTank(const placement_t *previousPlacement, const placement_t *currentPlacement, uint8_t color) {
    if (shouldRedraw(previousPlacement, currentPlacement)) {
        undrawTank(previousPlacement);
        drawTank(currentPlacement, color);
    }
}

static void processPlayer(level_t level, player_t *players, uint8_t index) {
    uint8_t i;
    placement_t previousPlacement = players[index].placement;

    processPlayerActionsInGame(players, index);

    // Player attributes
    movePlayer(players + index);

    if (players[index].weaponCooldown) {
        players[index].weaponCooldown--;
    }

    // Collision walls
    for (i = 0; i < bulletCount; i++) {
        playerCollideBullet(players, index, &bullets[i]);
    }

    // Collision powerups
    for (i = 0; i < powerUpCount; i++) {
        playerCollidePowerUp(players + index, powerUps, i);
    }

    for (i = 0; i < doorCount; i++) {
        // Note: Door collision is also handled in playerCollideWall!
        if (isDoorsOpen && entitiesCollide(players[index].placement, doors[i].placement)) {
            // TODO: This
        }
    }

    playerCollideWall(level, players + index);

    // Render purple tank
    renderTank(&previousPlacement, &players[index].placement, playerColor);
}

// Returns whether the bullet should be deleted
static uint8_t processBullet(level_t level, bullet_t *bullet) {
    placement_t previousPlacement = (*bullet).placement;

    moveBullet(bullet);

    // Collision
    if (bulletCollideWallAndShouldDelete(level, bullet)) {
        undrawBullet(&previousPlacement);
        return 1;
    }

    // Rendering
    if (shouldRedraw(&previousPlacement, &(*bullet).placement)) {
        undrawBullet(&previousPlacement);
        drawBullet(&(*bullet).placement, bulletColors[(*bullet).shotBy - 1]);
    }

    return 0;
}

static uint8_t processEnemy(level_t level, enemy_t *enemies, uint8_t index, vector_t *checkpoints) {
    uint8_t i;
    placement_t previousPlacement = enemies[index].placement;

    // Enemy attributes
    if (enemies[index].weaponCooldown) {
        enemies[index].weaponCooldown--;
    }

    //move and shoot
    processEnemyActions(players,playerCount,enemies,index, checkpoints);

    // Collision
    for (i = 0; i < bulletCount; i++) {
        // TODO: Maybe add fromPlayer property on bullet, so we don't have to pass all players in here?
        enemyCollideBullet(players, enemies + index, &bullets[i]);
    }
    for (i = 0; i < playerCount; i++) {
        enemyCollidePlayer(enemies + index, &players[i]);
    }
    enemyCollideWall(level, enemies + index);

    // Render yellow tank
    renderTank(&previousPlacement, &enemies[index].placement, enemyColor);

    return 0;
}

void processLivesAndScore(uint8_t previousScore[], uint8_t previousLives[], player_t* player, uint8_t numPlayers){
    uint8_t currentScore[MAX_PLAYERS];
    uint8_t currentLives[MAX_PLAYERS];
    uint8_t i;
    for (i = 0; i < numPlayers; i++) {
        currentScore[i] = players[i].points;
    }

    for (i = 0; i < numPlayers; i++) {
        currentLives[i] = players[i].lives;
    }

    for (i = 0; i < numPlayers; i++) {
        if (currentScore[i] != previousScore[i]) {
            livesAndScoreLcd(players, playerCount);
        }
    }

    for (i = 0; i < numPlayers; i++) {
        if (currentLives[i] != previousLives[i]) {
            livesAndScoreLcd(players, playerCount);
        }
    }


}

void deleteBullet(bullet_t *bullet){
    // Delete the bullet by moving the last entry into it, and deleting the last entry.
    undrawBullet(&(*bullet).placement);
    *bullet = bullets[bulletCount - 1];
    bulletCount--;
}

level_t processGameTick(level_t level) {
    uint8_t i;
    uint8_t previousScore[MAX_PLAYERS];
    uint8_t previousLives[MAX_PLAYERS];
    for (i = 0; i < playerCount; i++) {
        previousScore[i] = players[i].points;
    }

    for (i = 0; i < playerCount; i++) {
        previousLives[i] = players[i].lives;
    }


    // Process entities.
    // Each of these de-render each tick, so we can simply draw them at the new position in the end.
    for (i = 0; i < playerCount; i++) {
        processPlayer(level, players,i);
    }
    for (i = 0; i < bulletCount; i++) {
        if (processBullet(level,bullets + i)) {
            deleteBullet(bullets + i);
            i--;
        }
    }
    for (i = 0; i < enemyCount; i++) {
        if (processEnemy(level, enemies, i, enemyCheckpoints[i])) {
            // Delete the enemy by moving the last entry into it, and deleting the last entry.
            enemies[i] = enemies[enemyCount - 1];
            enemyCount--;
            i--;
        }
    }

    // Debug print current player rotation
    cursorToXY(40, 0);
    printf("%3i", players[0].placement.rotation);
    processLivesAndScore(previousScore, previousLives, players, playerCount);

    // Return invalidLevel to signal we don't want to change the level.
    return invalidLevel;
}



