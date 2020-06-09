#include "apps.h"
#define LEFT 1
#define TOP 1
#define RIGHT 41
#define BOTTOM 21
#define SIZE 20

void startBall(){
    drawWindow();
    ball_t ball = {6,6,1,2};

    int16_t counter = 0;
    while(1){

        if(counter == 0){
            updateBall(&ball);
        }

        counter++;
    }
}

void drawWindow(){
    walls(LEFT,TOP,RIGHT,BOTTOM);
    int8_t sTOP = (TOP + BOTTOM)/2 - 1;
    int8_t sBOTTOM = sTOP + 2;
    int8_t sLEFT = (LEFT + RIGHT)/2 - 4;
    int8_t sRIGHT = sLEFT + 7;
    walls(sLEFT,sTOP,sRIGHT,sBOTTOM);
}

void moveBall(ball_t *b){
    (*b).x += (*b).vx;
    (*b).y += (*b).vy;
}

void drawBall(ball_t *b){
    gotoxy((*b).x + LEFT,((*b).y / 2) + TOP);
    printf("o");
}

void undrawBall(ball_t *b){
    gotoxy((*b).x + LEFT,((*b).y / 2) + TOP);
    printf(" ");
}

void updateBall(ball_t *b){
    undrawBall(b);
    moveBall(b);


    int8_t collision = ballCollides(b);
    if(collision){
        bounceBall(b,collision);
        moveBall(b);
    }

    drawBall(b);
}

int8_t ballCollides(ball_t *b){
    int8_t collision = 0;
    if((*b).x <= 0){
        collision |= 1;
    }
    else if((*b).x >= RIGHT - LEFT){
        collision |= 4;
    }
    if((*b).y <= 0){
        collision |= 2;
    }
    else if((*b).y >= (BOTTOM - TOP)*2){
        collision |= 8;
    }
    return collision;
}

void bounceBall(ball_t *b, int8_t collision){
    if(collision & 5){
        (*b).vx *= -1;
    }
    if(collision & 10){
        (*b).vy *= -1;
    }
}
