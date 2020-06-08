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

#endif /* APPS_H_INCLUDED */
