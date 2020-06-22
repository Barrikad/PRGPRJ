#include <stdint.h>
#include "timer.h"

static volatile uint8_t flag = 0;
static volatile uint32_t framesSkipped = 0;

uint8_t getFrameFlag(){
    return flag;
}

uint32_t getFramesSkipped() {
    return framesSkipped;
}

static void setFrameFlag() {
    // If we tried to set the flag while it was set, we've missed processing a frame!
    // An indication that the game is running too slowly!
    if (flag) {
        framesSkipped++;
    }
    flag = 1;
}

void unsetFrameFlag(){
    flag = 0;
}

void initFrameTimer(uint16_t frequency) {
    disableTimer2();
    initTimer2WithFrequency(setFrameFlag, frequency);
    enableTimer2();
}
