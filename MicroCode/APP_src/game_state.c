#include "player.h"

//current max of 4 players
//array of players, and size of actually contained players
static uint8_t playersSize = 0;
static player_t* players[4];

//NOTE: enemies and bullets should probably be contained in linked list, to make removal easy

void addPlayer(player_t *player){
    players[playersSize] = player;
    playersSize++;
}

void movePlayers(){

}

uint8_t numberOfPlayers(){
    return playersSize;
}

player_t** allPlayers(){
    return players;
}
