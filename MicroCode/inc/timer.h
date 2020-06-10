#ifndef TIMER_H_
#define TIMER_H_
#include "stm32f30x.h"

void initTimer2();
void enableTimer2();
void disableTimer2();

typedef struct {
    int8_t hours;
    int8_t minutes;
    int8_t seconds;
    int8_t centiseconds;
} duration_t;

volatile duration_t currentDuration;

#endif /* TIMER_H_ */
