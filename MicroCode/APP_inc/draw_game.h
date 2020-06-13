#ifndef DRAW_GAME_H_INCLUDED
#define DRAW_GAME_H_INCLUDED

//functions map entities to sprites and coordinates, sent to the api

//assuming distinct player icons:
void drawPlayer1(player_t *player);
void drawPlayer2(player_t *player);

//assuming enemies stored in array
void drawEnemies(enemy_t *enemy, uint8_t numOfEnemies);

//assuming bullets stored in array
void drawBullets(bullet_t *bullet, uint8_t numOfBullets);



#endif /* DRAW_GAME_H_INCLUDED */
