#include "apps.h"
#define LEFT 1
#define TOP 1
#define RIGHT 41
#define BOTTOM 21
#define SIZE 20

void startBall(){
    drawWindow();
    ball_t ball = {6,6,2,2};
    int8_t counter = 0;
    /*while(1){
        if(counter%32 == 0){
            updateBall(&ball);
        }
        counter++;
    }*/
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
    drawBall(b);
}
