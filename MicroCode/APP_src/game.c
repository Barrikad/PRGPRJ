#include "game.h"
#include "player.h"
#include "door.h"
#include "bullet.h"
#include "enemy.h"
#include "power_up.h"
#include "level.h"
#include "ansi.h"
#include "graphics.h"
#include "enemy_ai.h"
#include "collision.h"
#include "door.h"
#include "frame_timer.h"
#include <stdio.h>
#include "player_stat_graphics.h"
#include "boss_mode.h"

#define MAX_PLAYERS 4
//array of players, and size of actually contained players
static uint8_t playerCount;
static player_t players[MAX_PLAYERS];

#define MAX_BULLETS 8
//actual number of bullets in bulletCount
static uint8_t bulletCount;
static bullet_t bullets[MAX_BULLETS];

#define MAX_ENEMIES 16
//actual number of enemies in enemyCount
static uint8_t enemyCount;
static enemy_t enemies[MAX_ENEMIES];
static vector_t enemyCheckpoints[MAX_ENEMIES][CHECKPOINT_COUNT];

#define MAX_POWERUPS 8
//actual number of bullets in bulletCount
static uint8_t powerUpCount;
static powerUp_t powerUps[MAX_POWERUPS];

#define MAX_DOORS 4
static uint8_t doorCount;
static door_t doors[MAX_DOORS];


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
    vector_t position;

    // Player at (2, 2) pointing downwards
    position.x = createFix(2);
    position.y = createFix(2);
    addPlayer(position, 128, movementFromJoystick);

    // Enemy at (38, 8) pointing downwards
    position.x = createFix(38);
    position.y = createFix(8);
    addEnemy(position, 128);

    // Enemy checkpoints
    vector_t cp1 = {createFix(38), createFix(11)};
    vector_t cp2 = {createFix(18), createFix(10)};
    vector_t cp3 = {createFix(18), createFix(7)};
    vector_t cp4 = {createFix(38), createFix(7)};
    enemyCheckpoints[0][0] = cp1;
    enemyCheckpoints[0][1] = cp2;
    enemyCheckpoints[0][2] = cp3;
    enemyCheckpoints[0][3] = cp4;
    enemyCheckpoints[0][4] = cp1;
    enemyCheckpoints[0][5] = cp2;
    enemyCheckpoints[0][6] = cp3;
    enemyCheckpoints[0][7] = cp4;

    // Motorcycle power-up at (24, 2)
    position.x = createFix(24);
    position.y = createFix(2);
    addPowerUp(position, 1);

    // Doors at bottom right
    position.x = createFix(38);
    position.y = createFix(12);
    addDoor(position, blockLevel);
    position.x = createFix(39);
    position.y = createFix(12);
    addDoor(position, blockLevel);
}


static void initLevel2() {
    vector_t position;

    // Player at (38.5, 1) pointing downwards
    position.x = createFix(38) + (createFix(1) >> 1);
    position.y = createFix(1);
    addPlayer(position, 128, movementFromJoystick);

    // Enemy at (16, 10) pointing right
    position.x = createFix(16);
    position.y = createFix(10);
    addEnemy(position, 0);

    // Enemy movement circle
    vector_t cp1 = {createFix(28), createFix(11)};
    vector_t cp2 = {createFix(33), createFix(7)};
    vector_t cp3 = {createFix(30), createFix(1)};
    vector_t cp4 = {createFix(19), createFix(2)};
    vector_t cp5 = {createFix(14), createFix(1)};
    vector_t cp6 = {createFix(6), createFix(3)};
    vector_t cp7 = {createFix(5), createFix(7)};
    vector_t cp8 = {createFix(12), createFix(10)};
    enemyCheckpoints[0][0] = cp1;
    enemyCheckpoints[0][1] = cp2;
    enemyCheckpoints[0][2] = cp3;
    enemyCheckpoints[0][3] = cp4;
    enemyCheckpoints[0][4] = cp5;
    enemyCheckpoints[0][5] = cp6;
    enemyCheckpoints[0][6] = cp7;
    enemyCheckpoints[0][7] = cp8;

    // Enemy at (3, 2) pointing downwards
    position.x = createFix(3);
    position.y = createFix(2);
    addEnemy(position, 128);

    // Enemy movement line-ish - forwards then backwards
    vector_t cp1_2 = {createFix(1), createFix(4)};
    vector_t cp2_2 = {createFix(1), createFix(9)};
    vector_t cp3_2 = cp1_2;
    vector_t cp4_2 = {createFix(3), createFix(1)};
    enemyCheckpoints[1][0] = cp1_2;
    enemyCheckpoints[1][1] = cp2_2;
    enemyCheckpoints[1][2] = cp3_2;
    enemyCheckpoints[1][3] = cp4_2;
    enemyCheckpoints[1][4] = cp1_2;
    enemyCheckpoints[1][5] = cp2_2;
    enemyCheckpoints[1][6] = cp3_2;
    enemyCheckpoints[1][7] = cp4_2;

    // Glide power-up at (20, 3)
    position.x = createFix(20);
    position.y = createFix(3);
    addPowerUp(position, 2);

    // Doors back
    position.x = createFix(38);
    position.y = createFix(0);
    addDoor(position, initialLevel);
    position.x = createFix(39);
    position.y = createFix(0);
    addDoor(position, initialLevel);

    // Doors to maze
    position.x = createFix(26);
    position.y = createFix(12);
    addDoor(position, mazeLevel);
    position.x = createFix(27);
    position.y = createFix(12);
    addDoor(position, mazeLevel);
}

static void initLevel3() {
    vector_t position;

    // Player at (26.5, 1) pointing right
    position.x = createFix(26) + (createFix(1) >> 1);
    position.y = createFix(1);
    addPlayer(position, 0, movementFromJoystick);

    // Enemy at (1.5, 1.5) pointing right
    position.x = createFix(1) + (createFix(1) >> 1);
    position.y = createFix(1) + (createFix(1) >> 1);
    addEnemy(position, 0);

    // No enemy movement
    enemyCheckpoints[0][0] = position;
    enemyCheckpoints[0][1] = position;
    enemyCheckpoints[0][2] = position;
    enemyCheckpoints[0][3] = position;
    enemyCheckpoints[0][4] = position;
    enemyCheckpoints[0][5] = position;
    enemyCheckpoints[0][6] = position;
    enemyCheckpoints[0][7] = position;

    // Doors back
    position.x = createFix(26);
    position.y = createFix(0);
    addDoor(position, blockLevel);
    position.x = createFix(27);
    position.y = createFix(0);
    addDoor(position, blockLevel);
}

void initLevel(level_t level) {
    // Reset all counts
    playerCount = 0;
    bulletCount = 0;
    enemyCount = 0;
    powerUpCount = 0;
    doorCount = 0;

    // Clear screen and hide cursor
    cursorHide();
    resetcolor();
    clrscr();

    // Render level with doors closed
    renderLevel(level);

    switch(level) {
    case initialLevel:
        initLevel1();
        initFrameTimer(100);
        break;
    case blockLevel:
        initLevel2();
        initFrameTimer(120);
        break;
    case mazeLevel:
        initLevel3();
        initFrameTimer(160);
        break;
    default:
        // Unreachable
        break;
    }

    // Initializes score and lives screen.
    livesAndScoreLcd(players, playerCount);
}


static uint8_t isDoorsOpen() {
    return enemyCount == 0;
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

void addEnemy(vector_t position, deg512_t rotation) {
    if (enemyCount >= MAX_ENEMIES) {
        return;
    }
    initEnemy(&enemies[enemyCount], position, rotation);
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

void renderPowerUps(){
    for(int i = 0; i < powerUpCount; i++){
        drawPowerUp(&powerUps[i].placement, powerUpColor, powerUps[i].effects & 2);
    }
}

static void renderTank(const placement_t *previousPlacement, const placement_t *currentPlacement, uint8_t color) {
    if (shouldRedraw(previousPlacement, currentPlacement)) {
        undrawTank(previousPlacement);
        drawTank(currentPlacement, color);
    }
}

static uint8_t processPlayer(player_t *players, uint8_t index) {
    uint8_t i;

    processPlayerActionsInGame(players, index);

    // Player attributes
    movePlayer(players + index);

    if (players[index].weaponCooldown) {
        players[index].weaponCooldown--;
    }

    // Collision walls
    for (i = 0; i < bulletCount; i++) {
        if (playerCollideBullet(players, index, &bullets[i])) {
            deleteBullet(&bullets[i]);
            i--;
        }
        if (players[index].lives == 0) {
            return 1;
        }
    }

    // Collision powerups
    for (i = 0; i < powerUpCount; i++) {
        playerCollidePowerUp(players + index, powerUps, i);
    }

    return 0;
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
        if (enemyCollideBullet(players, enemies + index, &bullets[i])) {
            deleteBullet(&bullets[i]);
            i--;
        }
        if (enemies[index].lives == 0) {
            undrawTank(&previousPlacement);
            return 1;
        }
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
    uint8_t i, j;
    placement_t previousPlacement;
    uint8_t previousScore[MAX_PLAYERS];
    uint8_t previousLives[MAX_PLAYERS];
    for (i = 0; i < playerCount; i++) {
        previousScore[i] = players[i].points;
    }

    for (i = 0; i < playerCount; i++) {
        previousLives[i] = players[i].lives;
    }

    //check if boss has entered office first of all
    //nothing is more important
    //game-stopping while loop, to make totally sure
    if(isBossKeyPressed()){
        renderBossMode(level);
    }


    // Process entities.
    // Each of these de-render each tick, so we can simply draw them at the new position in the end.
    for (i = 0; i < playerCount; i++) {
        previousPlacement = players[i].placement;
        if (processPlayer(players, i)) {
            undrawTank(&previousPlacement);
            // Delete the player by moving the last entry into it, and deleting the last entry.
            players[i] = players[playerCount - 1];
            playerCount--;
            i--;
            // Sorry, too lazy to not use a continue here ://
            continue;
        }

        for (j = 0; j < doorCount; j++) {
            // Note: Door collision is also handled in playerCollideWall!
            if (isDoorsOpen() && entitiesCollide(players[i].placement, doors[j].placement)) {
                return doors[j].nextLevel;
            }
        }

        playerCollideWall(level, players + i);

        // Render purple tank
        renderTank(&previousPlacement, &players[i].placement, playerColor);
    }

    // Exit game if playerCount is zero
    if (playerCount == 0) {
        // TODO: Move this somewhere else
        showScoreAfterDeath(previousScore);
        return invalidLevel;
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
            for (j = 0; j < CHECKPOINT_COUNT; j++) {
                enemyCheckpoints[i][j] = enemyCheckpoints[enemyCount - 1][j];
            }
            enemyCount--;
            i--;
            if (isDoorsOpen()) {
                // Draw doors as open
                for (j = 0; j < doorCount; j++) {
                    drawDoor(&doors[j].placement, doorColor, 1);
                }
            }
        }
    }

    // Debug print current player rotation
    cursorToXY(40, 0);
    printf("%3i", players[0].placement.rotation);
    processLivesAndScore(previousScore, previousLives, players, playerCount);


    // Return the current level to signal we don't want to change the level.
    return level;

}



