#include "boss_mode.h"
#include "ansi.h"
#include "keyboard.h"
#include "game.h"

void renderBossMode(level_t currentLevel) {
    clearKeys();
    clrscr();

    uint8_t fin = 0;
    while(!fin){
        fin = processInputBossMode();
    }

    renderLevel(currentLevel);
    renderPowerUps();
    clearKeys();
}

uint8_t processInputBossMode() {
    return keyHasBeenPressed(SPACE);
}

uint8_t isBossKeyPressed() {
    return keyHasBeenPressed(SPACE);
}
