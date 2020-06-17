#include "graphics.h"
#include "player.h"
#include "bullet.h"

static void drawPlayer(player_t player){
    drawSprite11(PLAYER,player.placement);
}

static void drawBullet(bullet_t bullet){
    drawSprite11(BULLET,bullet.placement);
}

void drawGame(player_t *players, uint8_t playerCount, bullet_t *bullets, uint8_t bulletCount) {

    // Draw players
    for(int i = 0; i < playerCount; i++) {
        drawPlayer(players[i]);
    }

    // DRAW BULLETS
    for(int i = 0; i < bulletCount; i++){
        drawBullet(bullets[i]);
    }
}

/*
//functions map entities to sprites and coordinates, sent to the api

//assuming enemies stored in array
void drawEnemies(enemy_t enemy, uint8_t numOfEnemies);

//assuming bullets stored in array
void drawBullets(bullet_t bullet, uint8_t numOfBullets);
*/
