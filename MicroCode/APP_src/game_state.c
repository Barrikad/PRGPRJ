#include "player.h"
#include "bullet.h"

//current max of 4 players
//array of players, and size of actually contained players
static uint8_t playerCount = 0;
static player_t players[4];

//max 512 bullets
//actual number of bullets in bulletCount
static uint16_t bulletCount = 0;
static bullet_t bullets[512];


//--------------PLAYERS-----------
void addPlayer(player_t player){
    players[playerCount] = player;
    playerCount++;
}

void movePlayers(){
    for(int i = 0; i < playerCount; i++){
        movePlayer(players + i);
    }
}

uint8_t numberOfPlayers(){
    return playerCount;
}

player_t* allPlayers(){
    return players;
}


//------------BULLETS-------------
void addBullet(bullet_t bullet){
    bullets[bulletCount] = bullet;
    bulletCount++;
}

void moveBullets(){
    for(int i = 0; i < bulletCount; i++){
        moveBullet(bullets + i);
    }
}

uint8_t numberOfBullets(){
    return bulletCount;
}

bullet_t* allBullets(){
    return bullets;
}
