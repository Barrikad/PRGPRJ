#include "enemy.h"
#include "player.h"

typedef struct{
    uint32_t distance;
    vector_t vec;
    player_t player;
} player_relation_t;

player_relation_t findClosestPlayer(player_t *players, uint8_t playerCount, enemy_t enemy) {
    //initialize search vars
    uint32_t minDistance = ~0;
    vector_t minVec;
    player_t closestPlayer;

    for(uint8_t i = 0; i < playerCount; i++){
        //find distance in x and y direction
        int32_t distance_x = (players[i].placement.position.x - enemy.placement.position.x);
        int32_t distance_y = (players[i].placement.position.y - enemy.placement.position.y);

        //multiplication, followed by conversion to integer, then addition
        //distance without square root since x < y -> sqrt(x) < sqrt(y)
        uint32_t distance = (distance_x * distance_x >> 14) + (distance_y * distance_y >> 14);

        //assign new closest player, if distance is smallest yet
        if(distance < minDistance){
            minVec.x = distance_x;
            minVec.y = distance_y;
            minDistance = distance;
            closestPlayer = players[i];
        }
    }

    //packing information. square root wasn't calculated above, so its done here
    player_relation_t pr = {squrt(minDistance),minVec,closestPlayer};
    return pr;
}

void processEnemyActions(player_t *players, uint8_t playerCount, enemy_t *enemies, uint8_t enemyCount) {
    for(uint8_t i = 0; i < enemyCount; i++){
        //---------------SHOT AT PLAYER---------------------------------------
        //find the player closest to the enemy, with distance information
        player_relation_t closestPR = findClosestPlayer(players, playerCount, enemies[i]);

        //formula for angle between vectors. The two vectors being vector from enemy to player
        //and unit-vector pointing right {1,0}.
        //acos((1*x + 0*y) / (1*sqrt(x^2+y^2))) = acos(x/dist)
        //https://onlinemschool.com/math/library/vector/angl/#:~:text=Basic%20relation.,the%20product%20of%20vector%20magnitude.
        deg512_t angle = acosine(closestPR.vec.x / closestPR.distance);

        //current rotation of enemy
        deg512_t enemyRotation = enemies[i].placement.rotation;

        //difference between rotation necessary to point at player, and current rotation
        //i.e. what would have to be added to enemy rotation to be aiming at player
        deg512_t rotationDiff = angle - enemyRotation;

        //rotate towards player
        //this is done even if currently pointing at player, as to create a spraying behavior
        if(rotationDiff > 0){
            enemies[i].placement.rotation += 8;
        }
        else{
            enemies[i].placement.rotation -= 8;
        }

        //shoot if pointing within approx 20 deg(base 360) to either side
        if(rotationDiff < 30 && rotationDiff > -30){
            fireBulletFromEnemy(&enemies[i]);
        }



        //------------------MOVE ENEMY---------------------------

    }
}
