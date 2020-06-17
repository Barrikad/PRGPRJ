#ifndef ENEMY_AI_H_INCLUDED
#define ENEMY_AI_H_INCLUDED

typedef struct {
    enemy_t* enemy;
    player_t* target;
} targeting;

//register an enemy to be affected by an input function.
//This function might have to be aware of the enemy to calculate a decision
void addEnemyWithInput(enemy_t* enemy, uint16_t (*inputFun)(enemy_t enemy));

//get input from all enemy input functions and realize the mapped actions
void processEnemyActionsInGame();


#endif /* ENEMY_AI_H_INCLUDED */
