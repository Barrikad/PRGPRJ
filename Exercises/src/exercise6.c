#include "stm32f30x_conf.h"
#include "30010_io.h"
#include "ansi.h"
#include "hardware_io.h"
#include "timer.h"
#include "exercise6.h"

typedef struct {
    int8_t hours;
    int8_t minutes;
    int8_t seconds;
    int8_t centiseconds;
} duration_t;

volatile duration_t currentDuration;

void printDuration(volatile duration_t * duration, uint8_t printCentiseconds) {
	if (duration == NULL) {
		printf(" -:--:--.--\n");
	} else if (printCentiseconds) {
		printf("%2i:%02i:%02i.%02i\n", duration->hours, duration->minutes, duration->seconds, duration->centiseconds);
	} else {
		printf("%2i:%02i:%02i.--\n", duration->hours, duration->minutes, duration->seconds);
	}
}

void clearDurations() {
	gotoxy(20, 3);
	printDuration(&currentDuration, 1);
	gotoxy(20, 4);
	printDuration(NULL, 1);
	gotoxy(20, 5);
	printDuration(NULL, 1);
}

void incrementDuration() {
    // Increment the duration by one hundredth of a second every time the interrupt runs
	currentDuration.centiseconds++;
	if (currentDuration.centiseconds > 99) {
		currentDuration.centiseconds = 0;
		currentDuration.seconds++;
	}
	if (currentDuration.seconds > 59) {
		currentDuration.seconds = 0;
		currentDuration.minutes++;
	}
	if (currentDuration.minutes > 59) {
		currentDuration.minutes = 0;
		currentDuration.hours++;
	}
}

void exercise6() {
    clrscr();
    initJoystick();
    // 100Hz timer
    initTimer2(0, 640000 - 1, incrementDuration);

    uint8_t timerEnabled = 0;
	uint8_t previousJoystick = 0;
	uint8_t previousSeconds = 0;

	window(0, 0, 32, 5, "Stop watch", 0);
	gotoxy(2, 3);
	printf("Time since start:");
	gotoxy(2, 4);
	printf("Split time 1:");
	gotoxy(2, 5);
	printf("Split time 2:");
	clearDurations();
    while(1) {
		// TODO: Detect button release event instead?
    	uint8_t currentJoystick = readJoystick();
    	if (currentJoystick != previousJoystick) {
			previousJoystick = currentJoystick;
    		// Toggle the timer when the middle button is pressed
            if (currentJoystick & 0x10) {
            	if (timerEnabled) {
            		disableTimer2();
            		gotoxy(20, 3);
            		printDuration(&currentDuration, 1);
            		timerEnabled = 0;
            	} else {
                	enableTimer2();
            		gotoxy(20, 3);
            		printDuration(&currentDuration, 0);
            		timerEnabled = 1;
            	}
            }
            // Stop the timer when the down button is pressed
			if (currentJoystick & 0x02) {
				disableTimer2();
				currentDuration.hours = 0;
				currentDuration.minutes = 0;
				currentDuration.seconds = 0;
				currentDuration.centiseconds = 0;
				timerEnabled = 0;
				clearDurations();
			}
            // Print split time 1 when the left button is pressed
			if (currentJoystick & 0x04) {
				// TODO: Disable the timer before reading the full duration?
				gotoxy(20, 4);
				printDuration(&currentDuration, 1);
			}
            // Print split time 2 when the right button is pressed
			if (currentJoystick & 0x08) {
				// TODO: Disable the timer before reading the full duration?
				gotoxy(20, 5);
				printDuration(&currentDuration, 1);
			}
    	}
    	// TODO: currentDuration.seconds could change in the meantime?
    	if (previousSeconds != currentDuration.seconds) {
    		previousSeconds = currentDuration.seconds;
    		gotoxy(20, 3);
    		printDuration(&currentDuration, 0);
    	}
    }
}
