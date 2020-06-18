#include "enemy.h"
#include "player.h"

player_t findClosestPlayer(player_t *players, uint8_t playerCount, enemy_t enemy) {
    //initialize search vars
    uint32_t minDistance = ~0;
    player_t closestPlayer;

    for(uint8_t i = 0; i < playerCount; i++){
        //find distance in x and y direction
        int32_t distance_x = (players[i].placement.position.x - enemy.placement.position.x);
        int32_t distance_y = (players[i].placement.position.y - enemy.placement.position.y);
        vector_t distance_v = {distance_x,distance_y};

        uint32_t distance = vectorLen(distance_v);

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
        //find the player closest to the enemy
        player_t closestPlayer = findClosestPlayer(players, playerCount, enemies[i]);

        //x and y values of vector from enemy to player
        fix14_t diff_x = closestPlayer.placement.position.x - enemies[i].placement.position.x;
        fix14_t diff_y = closestPlayer.placement.position.y - enemies[i].placement.position.y;

        //distance from enemy to player
        vector_t diff_v = {diff_x,diff_y};

        //formula for angle between vectors. The two vectors being vector from enemy to player
        //and unit-vector pointing right {1,0}.
        //https://onlinemschool.com/math/library/vector/angl/#:~:text=Basic%20relation.,the%20product%20of%20vector%20magnitude.
        deg512_t angle = acosine((1*diff_x) / 1);
    }
}
