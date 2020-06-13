#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

typedef struct{
    vector_t position;
    vector_t velocity;
    fix14_t rotation;
    uint8_t lives;
    uint8_t points;
} enemy_t;

void moveEnemy(enemy_t *enemy);

void setEnemyVelocity(enemy_t *enemy, vector_t velocity);

void damageEnemy(enemy_t *enemy, uint8_t damage);

void fireBullet(enemy_t *enemy);

#endif /* ENEMY_H_INCLUDED */
