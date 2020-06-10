#include "stm32f30x_conf.h"
#include "30010_io.h"
#include "ansi.h"
#include "hardwareIO.h"
#include "timer.h"

#ifndef EXERCISE6_H_
#define EXERCISE6_H_

#define PRESCALER_SW 63999
#define RELOAD_SW 9

void exercise6();

typedef struct {
    int8_t hours;
    int8_t minutes;
    int8_t seconds;
    int8_t centiseconds;
} duration_t;

volatile duration_t currentDuration;

#endif /* EXERCISE6_H_ */
