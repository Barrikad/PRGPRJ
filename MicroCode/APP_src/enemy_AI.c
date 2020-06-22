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
        //find distance in x and y direction, converted to fix8
        fix14_t distance_x = (players[i].placement.position.x - enemy.placement.position.x);
        fix14_t distance_y = (players[i].placement.position.y - enemy.placement.position.y);

        //ready values for distance calculation. because of the squaring we can take absolute value
        //one could just use vectorLen here, but that would require unnecessary squaring
        int32_t distance_xT = distance_x;
        int32_t distance_yT = distance_y;
        if(distance_xT < 0){
            distance_xT = -distance_xT;
        }
        if(distance_yT < 0){
            distance_yT = -distance_yT;
        }
        //convert to fix5 to avoid overflow;
        distance_xT >>= 9;
        distance_yT >>= 9;

        //multiplication (converting to fix10), addition, then conversion to fix14
        //distance without square root since x < y -> sqrt(x) < sqrt(y)
        uint32_t distance = ((distance_xT * distance_xT) + (distance_yT * distance_yT)) << 4;

        //assign new closest player, if distance is smallest yet
        if(distance < minDistance){
            //converting back to fix14
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

void processEnemyActions(player_t *players, uint8_t playerCount, enemy_t *enemies, uint8_t index, vector_t *checkpoints) {
    //TODO: shooting and moving should probably be pulled into separate functions
    //---------------SHOT AT PLAYER---------------------------------------
    //find the player closest to the enemy, with distance information
    player_relation_t closestPR = findClosestPlayer(players, playerCount, enemies[index]);


    //formula for angle between vectors. The two vectors being vector from enemy to player
    //and unit-vector pointing right {1,0}.
    //acos((1*x + 0*y) / (1*sqrt(x^2+y^2))) = acos(x/dist)
    //https://onlinemschool.com/math/library/vector/angl/#:~:text=Basic%20relation.,the%20product%20of%20vector%20magnitude.
    fix14_t cosa = FIX14_DIV(absFix(closestPR.vec.x), closestPR.distance);
    deg512_t angle;
    if(closestPR.vec.x >= 0){
        angle = acosine(cosa);
    }
    else{
        //negative angle must be reduced to within bounds
        angle = acosine(-cosa);
    }
    //if player is above enemy we've have the angle anti-clockwise
    //must be converted to angle clockwise
    if(closestPR.vec.y < 0){
        angle = 512 - angle;
    }

    //current rotation of enemy
    deg512_t enemyRotation = enemies[index].placement.rotation;

    //difference between rotation necessary to point at player, and current rotation
    //i.e. what would have to be added to enemy rotation to be aiming at player
    deg512_t rotationDiff = angle - enemyRotation;


    //rotate towards player
    //this is done even if currently pointing at player, as to create a spraying behavior
    if(rotationDiff > 0){
        enemies[index].placement.rotation += 2;
    }
    else{
        enemies[index].placement.rotation -= 2;
    }

    //shoot if pointing within approx 20 deg(base 360) to either side
    if(rotationDiff < 30 && rotationDiff > -30){
        fireBulletFromEnemy(enemies,index);
    }



    //------------------MOVE ENEMY---------------------------
    //TODO: should make a better naming convention, but might want to extract function first
    //distance to checkpoint in either direction
    fix14_t cpDiffX = checkpoints[enemies[index].checkpointIndex].x - enemies[index].placement.position.x;
    fix14_t cpDiffY = checkpoints[enemies[index].checkpointIndex].y - enemies[index].placement.position.y;

    //find distance to checkpoint
    vector_t cpDiffV = {cpDiffX,cpDiffY};
    fix14_t cpDist = vectorLen(cpDiffV);

    if(cpDist < (1 << 14)){
        //if distance is less than one move on to next checkpoint
        enemies[index].checkpointIndex++;
        enemies[index].checkpointIndex %= CHECKPOINT_COUNT;
    }else{
        //else move closer to checkpoint

        //reduce distance vector to unit vector
        cpDiffX = FIX14_DIV(cpDiffX,cpDist);
        cpDiffY = FIX14_DIV(cpDiffY,cpDist);

        // And reduce further yet to a speed of 1 << 9 (same as player)
        // TODO: Verify the correctness of this!
        cpDiffX = cpDiffX >> 5;
        cpDiffY = cpDiffY >> 5;

        //add unit vector pointing to checkpoint to enemy position
        enemies[index].placement.position.x += cpDiffX;
        enemies[index].placement.position.y += cpDiffY;
    }
}
