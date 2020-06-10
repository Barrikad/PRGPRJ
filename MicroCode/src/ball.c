#include "ball.h"
#define LEFT 1
#define TOP 1
#define RIGHT 41
#define BOTTOM 21
#define SIZE 20

// Sets up the initial values to make the function run.
void startBall(){
    drawWindow();
    ball_t ball = {(6 << 14) , (6 << 14) , (1 << 14) + (5 << 13), (2 << 14) };

    int16_t counter = 0;
    uint16_t collisions = 0;
    while(1){

        if(counter == 0){
            updateBall(&ball, &collisions);
        }

        counter++;
    }
}

// Draws the window for the ball and counter.
void drawWindow(){
    walls(LEFT,TOP,RIGHT,BOTTOM);
    int8_t sTOP = (TOP + BOTTOM)/2 - 1;
    int8_t sBOTTOM = sTOP + 2;
    int8_t sLEFT = (LEFT + RIGHT)/2 - 6;
    int8_t sRIGHT = sLEFT + 13;
    walls(sLEFT,sTOP,sRIGHT,sBOTTOM);
    gotoxy(sLEFT + 1, sTOP + 1);
    printf("Hits: 0");
}

// Moves the ball in direction of the velocity
// Parameteres:     *b: a ball.
void moveBall(ball_t *b){
    (*b).x += (*b).vx;
    (*b).y += (*b).vy;
}


// Draws the ball on the terminal
// Parameters:      *b a ball.
void drawBall(ball_t *b){
    gotoxy(((*b).x >> 14) + LEFT,((*b).y >> 14)/2 + TOP);
    printf("o");
}

// Removes the drawing of the ball
// Parameters:      *B a ball.
void undrawBall(ball_t *b){
    gotoxy(((*b).x >> 14) + LEFT,((*b).y >> 14)/2 + TOP);
    printf(" ");
    // The function draws an empty space to remove the ball from the last location.
}

// Update the balls position on terminal
// Parameters:      *b a ball.
//                  *collisions a counter
void updateBall(ball_t *b, uint16_t * collisions){
    undrawBall(b);
    moveBall(b);


    int8_t collision = ballCollides(b);
    if(collision){
    	(*collisions)++;
        bounceBall(b,collision);
        moveBall(b);
        int8_t sTOP = (TOP + BOTTOM)/2 - 1;
        int8_t sLEFT = (LEFT + RIGHT)/2 - 6;
        gotoxy(sLEFT + 7, sTOP + 1);
        printf("%i", *collisions);
    }

    drawBall(b);
    // The function removes the previous ball, then updates the ball position.
    // Then checks if there has been a collision. If there has been a collision'
    // the balls velocity is change, and its position is then updated accordingly.
    // The collision counter on the screen us update. The ball is drawn in its new
    // position.
}


// Check which wall the ball collides with.
// Parameters:      *b a ball.
int8_t ballCollides(ball_t *b){
    int8_t collision = 0;
    if((*b).x <= 0){
        collision |= 1;
    }
    else if(((*b).x) >> 14 >= RIGHT - LEFT){
        collision |= 4;
    }
    if((*b).y <= 0){
        collision |= 2;
    }
    else if(((*b).y) >> 14 >= (BOTTOM - TOP)*2){
        collision |= 8;
    }
    return collision;
}

// Changes the velocity of the ball
// Parameters:      *b a ball.
//                  collision a bit value
void bounceBall(ball_t *b, int8_t collision){
    if(collision & 5){
        (*b).vx = -(*b).vx;
    }
    if(collision & 10){
        (*b).vy = -(*b).vy;
    }

    // The function takes the ball and the collision and change the velocity
    // of the ball according to which wall was hit.
}
