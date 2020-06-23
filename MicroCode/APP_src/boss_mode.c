#include "boss_mode.h"
#include "ansi.h"
#include "keyboard.h"

void renderBossMode() {
    clearKeys();
    clrscr();

    uint8_t fin = 0;
    while(!fin){
        fin = processInputBossMode();
    }

    clearKeys();
}

uint8_t processInputBossMode() {
    return keyHasBeenPressed(SPACE);
}

uint8_t isBossKeyPressed() {
    return keyHasBeenPressed(SPACE);
}
