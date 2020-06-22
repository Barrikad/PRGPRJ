#include <stdint.h>
#include "timer.h"

static volatile uint8_t flag = 0;
static volatile uint32_t framesSkipped = 0;

uint8_t getFlag(){
    return flag;
}

uint32_t getFramesSkipped() {
    return framesSkipped;
}

static void setFlag() {
    // If we tried to set the flag while it was set, we've missed processing a frame!
    // An indication that the game is running too slowly!
    if (flag) {
        framesSkipped++;
    }
    flag = 1;
}

void unsetFlag(){
    flag = 0;
}

void initFrameTimer() {
    initTimer2WithFrequency(setFlag, 100);
    enableTimer2();
}
