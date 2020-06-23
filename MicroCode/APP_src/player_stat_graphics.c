#include <stdio.h>
#include "player.h"
#include "lcd.h"
#include "player_stat_graphics.h"
#include <string.h>
#include "falling_edge_selection.h"


// Gets player score and transforms it to a char array.
static void getScore(char score[3][14], player_t* players, uint8_t numPlayers){
    for (int i = 0; i < 3; i++) {
        sprintf(score[i], "%6d",players[i].points);
    }
}

// Gets player lives a transforms it to a char array.
static void getLives(char numLives[3][4], player_t* players, uint8_t numPlayers){
    for (int i = 0; i < numPlayers; i++) {
        sprintf(numLives[i], "%3d",players[i].lives);
    }
}

// Renders the players lives and score on LCD screen.
void livesAndScoreLcd(player_t* players, uint8_t numPlayers) {
    char* header = {"         Score: Lives:"};
    char* playerName[] = {"Player 1", "Player 2", "Player 3"};
    char score[3][14];
    char numLives[3][4];
    uint8_t i;
    uint8_t j;
    lcdClear();

    for (i = 0; i < strlen(header); i++) {
        lcdWriteChar(header[i], i * 6, 0);
    }

    for (i = 0; i < numPlayers; i++) {
        for (j = 0; j < strlen(playerName[i]); j++) {
            lcdWriteChar(playerName[i][j], j * 6, (i+1) * 8);
        }
    }

    getScore(score, players, numPlayers);

    for (i = 0; i < numPlayers; i++) {
        for (j = 0; j < 6; j++) {
                lcdWriteChar(score[i][j], (j + 9) * 6, (i + 1) * 8);
        }
    }

    getLives(numLives, players, numPlayers);

    for (i = 0; i < numPlayers; i++) {
        for (j = 0; j < 3; j++) {
            lcdWriteChar(numLives[i][j], (j+18) * 6, (i+1) * 8);
        }
    }

    lcdFlush();
}

void showScoreAfterDeath(player_t* players, uint8_t numPlayers) {
    char* gameOver = {"GAMEOVER       Score:"};
    char* playerName[] = {"Player 1", "Player 2", "Player 3"};
    char* help = {"               <-Back"};
    char score[3][14];
    uint8_t i;
    uint8_t j;
    lcdClear();

     for (i = 0; i < strlen(gameOver); i++) {
        lcdWriteChar(gameOver[i], i * 6, 0);
    }

    for (i = 0; i < 3; i++) {
        for (j = 0; j < strlen(playerName[i]); j++) {
            lcdWriteChar(playerName[i][j], j * 6, (i+1) * 8);
        }
    }

    getScore(score, players, numPlayers);

    for (i = 0; i < numPlayers; i++) {
        for (j = 0; j < 6; j++) {
                lcdWriteChar(score[i][j], (j + 15) * 6, (i + 1) * 8);
        }
    }

    for (j = 0; j < 21; j++) {
            lcdWriteChar(help[j], j*6, 3*8);
    }


    lcdFlush();
}

uint8_t leaveScoreScreen() {
    if (hasPressedLeft()){
        return 1;
    }
    return 0;
}
