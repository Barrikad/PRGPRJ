#include "exercise7.h"

volatile uint8_t lcdShouldUpdate = 0;

void setLcdUpdateFlag() {
	lcdShouldUpdate = 1;
}

void exercise7() {
	uint8_t buffer[LCD_BUFFER_SIZE];
	uint32_t tick = 0;
	lcd_init();
	lcd_clear(buffer);
	// 100Hz timer
    initTimer2(0, 640000 - 1, setLcdUpdateFlag);
    enableTimer2();

	while(1) {
		if (lcdShouldUpdate) {
			lcdShouldUpdate = 0;
			lcd_update(buffer, "Test 123", tick);
			tick++;
		}
	}
}
