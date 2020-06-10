#include "lcd.h"

static uint8_t buffer[512];

void lcdInit() {
	lcd_init();
}

// Clear the internal LCD buffer
void lcdClear() {
	memset(buffer, 0x00, LCD_BUFFER_SIZE);
}

// Flush the buffer to the LCD
void lcdFlush() {
	lcd_push_buffer(buffer);
}

// Write
void lcdWriteString(char * string, uint8_t line, uint8_t slice) {
	uint8_t i, j;
	const char * charData;
	// Clear buffer
	lcdClear();
	// Loop over each character in the string
	for (i = 0; string[i]; i++) {
		charData = character_data[string[i] - 0x20];
		for (j = 0; j < 5; j++) {
			buffer[line*128 + slice + i * 6 + j] = charData[j];
		}
	}
}

void lcdUpdate() {
    for (int i = 0; i < 4; i++) {
        uint8_t first = buffer[i*128];
        for (int j = 0; j < 127; j++) {
            buffer[i*128 + j] = buffer[i*128 + j + 1];
        }
        buffer[i*128 + 127] = first;
    }
}
