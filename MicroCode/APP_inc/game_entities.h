#ifndef GAME_ENTITIES_H_INCLUDED
#define GAME_ENTITIES_H_INCLUDED

void addPlayer(player_t *player);
void addEnemy(enemy_t *enemy);
void addBullet(bullet_t *bullet);

void movePlayers();
void moveEnemies();
void moveBullets();

void processCollisions();

#endif /* GAME_ENTITIES_H_INCLUDED */
