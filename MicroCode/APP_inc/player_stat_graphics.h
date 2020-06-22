#ifndef PLAYER_STAT_GRAPHICS_H_INCLUDED
#define PLAYER_STAT_GRAPHICS_H_INCLUDED


// Show the score and lives on the LCD
void livesAndScoreLcd(player_t* players, uint8_t numPlayers);

// Show the score of the player after death.
uint8_t scoreAfterDeath(player_t* players, uint8_t numPlayers);


#endif /* PLAYER_STAT_GRAPHICS_H_INCLUDED */
