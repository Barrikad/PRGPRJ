#include "player.h"
#include "bullet.h"

//current max of 4 players
//array of players, and size of actually contained players
static uint8_t playersSize = 0;
static player_t* players[4];

//NOTE: enemies and bullets should probably be contained in linked list, to make removal easy
static uint16_t bulletsSize = 0;
static bullet_t* bullets[512];


//--------------PLAYERS-----------
void addPlayer(player_t *player){
    players[playersSize] = player;
    playersSize++;
}

void movePlayers(){
    for(int i = 0; i < playersSize; i++){
        movePlayer(players[i]);
    }
}

uint8_t numberOfPlayers(){
    return playersSize;
}

player_t** allPlayers(){
    return players;
}


//------------BULLETS-------------
void addBullet(bullet_t *bullet){
    bullets[bulletsSize] = bullet;
    bulletsSize++;
}

void moveBullets(){
    for(int i = 0; i < bulletsSize; i++){
        moveBullet(bullets[i]);
    }
}

uint8_t numberOfBullets(){
    return bulletsSize;
}

bullet_t** allBullets(){
    return bullets;
}
