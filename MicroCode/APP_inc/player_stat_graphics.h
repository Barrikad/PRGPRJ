#ifndef PLAYER_STAT_GRAPHICS_H_INCLUDED
#define PLAYER_STAT_GRAPHICS_H_INCLUDED


// Show the score and lives on the LCD when the player is alive
void livesAndScoreLcd(player_t* players, uint8_t numPlayers);

// Show the score of the player after death.
void showScoreAfterDeath(uint8_t scores[]);


#endif /* PLAYER_STAT_GRAPHICS_H_INCLUDED */
