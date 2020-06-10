#ifndef STOPWATCH_H_INCLUDED
#define STOPWATCH_H_INCLUDED
#define PRESCALER_SW 63999
#define RELOAD_SW 9
#include <stdint.h>
#include <stdio.h>

typedef struct{
    uint8_t centiSeconds, seconds, minutes, hours;
} time_struc;


void increaseCenti();

void printTime();

uint8_t curSecond();


#endif /* STOPWATCH_H_INCLUDED */
