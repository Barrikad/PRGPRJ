#ifndef MOVEMENT_H_INCLUDED
#define MOVEMENT_H_INCLUDED

typedef uint8_t mover_t;
const mover_t PLAYER_MOVER = 1;

//this gets the direction of a mover is moving.
direction_t moversDirection(mover_t mover);

#endif /* MOVEMENT_H_INCLUDED */
