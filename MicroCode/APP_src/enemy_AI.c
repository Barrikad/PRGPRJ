#include "enemy.h"
#include "player.h"

player_t findClosestPlayer(player_t *players, uint8_t playerCount, enemy_t enemy) {
    //initialize search vars
    uint16_t minDistance = ~0;
    player_t closestPlayer;

    for(uint8_t i = 0; i < playerCount; i++){
        //converting distance to fix7, for easier multiplication later
        int32_t distance_x = (players[i].placement.position.x - enemy.placement.position.x) >> 7;
        int32_t distance_y = (players[i].placement.position.y - enemy.placement.position.y) >> 7;

        //multiplication, followed by conversion to integer, then addition
        uint16_t distance = (distance_x * distance_x >> 14) + (distance_y * distance_y >> 14);

        //assign new closest player, if distance is smallest yet
        if(distance < minDistance){
            minDistance = distance;
            closestPlayer = players[i];
        }
    }
    return closestPlayer;
}

void processEnemyActions(player_t *players, uint8_t playerCount, enemy_t *enemies, uint8_t enemyCount) {
    for(uint8_t i = 0; i < enemyCount; i++){
        player_t closestPlayer = findClosestPlayer(players, playerCount, enemies[i]);
    }
}
