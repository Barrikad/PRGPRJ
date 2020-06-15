#include <stdio.h>
#include <stdint.h>
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h"
#include "stm32f30x.h"
#include "player.h"
#include "entity_representation.h"
#include "fix_point_math.h"
#include "game_state.h"


int main(void)
{
    uart_init(115200);

    deg512_t rot = 0;
    vector_t pos = {4,4};
    vector_t hb = {1,1};
    placement_t plc= {pos,hb,rot};
    vector_t vel = {0,0};
    player_t player = {plc,vel,0,0,0};

    addPlayer(&player);

    drawGame();

    while(1){

    }
}
