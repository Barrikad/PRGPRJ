#ifndef PLAYER_STAT_GRAPHICS_H_INCLUDED
#define PLAYER_STAT_GRAPHICS_H_INCLUDED


// Show the score and lives on the LCD
void livesAndScoreLcd(player_t* players, uint8_t numPlayers);

// Show the score of the player after death.
void showScoreAfterDeath(player_t* players, uint8_t numPlayers) ;

// Tells when the player want to leave the score screen.
uint8_t leaveScoreScreen();


#endif /* PLAYER_STAT_GRAPHICS_H_INCLUDED */
