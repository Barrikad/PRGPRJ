#include "stopwatch.h"

static time_struc curTime = {99,59,59,23};

void increaseCenti() {
    curTime.centiSeconds += 1;

    if(curTime.centiSeconds >= 100){
    curTime.centiSeconds = 0;
    curTime.seconds += 1;

    if(curTime.seconds >= 60){
    curTime.seconds = 0;
    curTime.minutes += 1;

    if(curTime.minutes >= 60){
    curTime.minutes = 0;
    curTime.hours += 1;
    curTime.hours %= 24;
    }
    }
    }
}

void printTime(){
    printf("%2i:%2i:%2i:%3i\n",curTime.hours,curTime.minutes,curTime.seconds,curTime.centiSeconds);
}

uint8_t curSecond(){
    return curTime.seconds;
}
