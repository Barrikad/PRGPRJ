#include <stdio.h>
#include "player.h"
#include "lcd.h"
#include "player_stat_graphics.h"
#include <string.h>


// Gets player score and transforms it to a char array.
static void getScore(char score[3][14], player_t* players, uint8_t numPlayers){
    for (int i = 0; i < numPlayers; i++) {
        sprintf(score[i], "%6d",players[i].points);
    }
}

// Gets player lives a transforms it to a char array.
static void getLives(char numLives[3], player_t* players, uint8_t numPlayers){
    for (int i = 0; i < numPlayers; i++) {
        sprintf(numLives, "%d",players[i].lives);
    }
}

// Renders the players lives and score on LCD screen.
void livesAndScoreLcd(player_t* players, uint8_t numPlayers) {
    char* header = {"         Score: Lives:"};
    char* playerName[] = {"Player 1", "Player 2", "Player 3"};
    char score[3][14];
    char numLives[3];
    lcdClear();

    for (int i = 0; i < strlen(header); i++) {
        lcdWriteChar(header[i], i * 6, 0);
    }

    for (int i = 0; i < numPlayers; i++) {
        for (int j = 0; j < strlen(playerName[i]); j++) {
            lcdWriteChar(playerName[i][j], j * 6, (i+1) * 8);
        }
    }

    getScore(score, players, numPlayers);

    for (int i = 0; i < numPlayers; i++) {
        for (int j = 0; j < 6; j++) {
                lcdWriteChar(score[i][j], (j + 9) * 6, (i + 1) * 8);
        }
    }

    getLives(numLives, players, numPlayers);

    for (int i = 0; i < numPlayers; i++) {
            lcdWriteChar(numLives[i], 20 * 6, (i+1) * 8);
    }

    lcdFlush();
}


