#include <stdio.h>
#include "player.h"
#include "lcd.h"
#include "player_stat_graphics.h"
#include <string.h>

static void getScore(char score[3][14], player_t* players, uint8_t numPlayers){
    for (int i = 0; i < numPlayers; i++) {
        sprintf(score[i], "%6d",players[i].points);
    }
}

void livesAndScoreLcd(player_t* players, uint8_t numPlayers) {
    char* header = {"        Score:  Lives:"};
    char* playerName[] = {"Player 1", "Player 2", "Player 3"};
    char score[3][14];
    lcdClear();

    for (int i = 0; i < strlen(header); i++) {
        lcdWriteChar(header[i], i * 6, 0);
    }

    for (int i = 1; i < (numPlayers + 1); i++) {
        for (int j = 0; j < strlen(playerName[i-1]); j++) {
            lcdWriteChar(playerName[i-1][j], j * 6, i * 8);
        }
    }

    getScore(score, players, numPlayers);

    for (int i = 1; i < (numPlayers + 1); i++) {
        for (int j = 9; j < 15; j++) {
                lcdWriteChar(score[i][j], j * 6, i * 8);
        }
    }

    for (int i = 1; i < (numPlayers + 1); i++) {
            lcdWriteChar(players[i].lives, 20 * 6, i * 8);
    }

    lcdFlush();
}


