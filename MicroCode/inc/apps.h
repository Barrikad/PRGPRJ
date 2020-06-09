#include <stdint.h>
#include <stdio.h>
#include "arithmatic.h"
#include "ansi.h"
#ifndef APPS_H_INCLUDED
#define APPS_H_INCLUDED

typedef struct {
    int32_t x,y,vx,vy;
} ball_t;

void startBall();
void drawWindow();
void moveBall(ball_t *b);
void drawBall(ball_t *b);
void undrawBall(ball_t *b);
void updateBall(ball_t *b, int8_t * collisions);
int8_t ballCollides(ball_t *b);
void bounceBall(ball_t *b, int8_t collision);


#endif /* APPS_H_INCLUDED */
