#include "graphics.h"
#include "game_state.h"

static void drawPlayer(player_t player){
    drawSprite11(PLAYER,player.placement);
}

void drawGame(){
    //Number of PlayerS
    uint8_t nps = numberOfPlayers();
    //array of pointers to players
    player_t** players = allPlayers();

    for(int i = 0; i < nps; i++){
        //reference right pointer, then the player referenced by that pointer
        drawPlayer(*(*(players + i)));
    }
}

/*
//functions map entities to sprites and coordinates, sent to the api

//assuming enemies stored in array
void drawEnemies(enemy_t enemy, uint8_t numOfEnemies);

//assuming bullets stored in array
void drawBullets(bullet_t bullet, uint8_t numOfBullets);
*/
