#include "exercise7.h"

volatile uint8_t lcdShouldUpdate = 0;

void setLcdUpdateFlag() {
	lcdShouldUpdate = 1;
}

void exercise7() {
	uint32_t tick = 0;
	lcdInit();
	lcdClear();
	// 100Hz timer
    initTimer2(0, 640000 - 1, setLcdUpdateFlag);
    enableTimer2();

    lcdWriteString("hello world", 0, 1);
	lcdFlush();

	while(1) {
		if (lcdShouldUpdate) {
			lcdShouldUpdate = 0;
			lcdUpdate();
			lcdFlush();
			tick++;
		}
	}
}
