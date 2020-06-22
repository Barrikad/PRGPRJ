#include <stdint.h>
#include "timer.h"

static uint8_t flag = 0;

uint8_t getFlag(){
    return flag;
}

static void setFlag(){
    flag = 1;
}

void unsetFlag(){
    flag = 0;
}

void initFrameTimer() {
    initTimer2WithFrequency(setFlag, 100);
    enableTimer2();
}
