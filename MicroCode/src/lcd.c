#include "lcd.h"
#include "30010_io.h"
#include "charset.h"
#include <string.h>

#define LCD_BUFFER_SIZE 512
#define LCD_WIDTH 128
#define LCD_HEIGHT 32

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

void lcdWriteHorizontalLine(uint8_t line, int8_t x, int8_t y) {
	// TODO: This
}

void lcdWriteVerticalLine(uint8_t line, int8_t x, int8_t y) {
	// TODO: Make `y` work in this.
	buffer[x + (y / 8) * LCD_WIDTH] = line;
}

// Write a character into the buffer at the specified location.
// Letting parts of the character go outside the screen is allowed.
// TODO: Make `y` work in this.
void lcdWriteChar(char chr, int8_t x, int8_t y) {
	int8_t i;
	// Note: We don't detect overflow here!
	const char * charData = character_data[chr - 0x20];
	for (i = 0; i < 5; i++) {
		// Don't write anything if the position is outside the screen
		// The fact that `x` is signed is desired, this lets us implement scrolling text easily.
		if (x + i < 0 || x + i >= LCD_WIDTH) {
			continue;
		}
		lcdWriteVerticalLine(charData[i], x + i, y);
	}
}

void lcdWriteString(char * string, uint8_t line, uint8_t slice) {
	uint8_t i;
	// Loop over each character in the string
	for (i = 0; string[i]; i++) {
		lcdWriteChar(string[i], line*LCD_WIDTH + slice + i * 6, 0);
		lcdWriteChar(string[i], line*LCD_WIDTH + slice + i * 6, 10);
	}
	lcdWriteChar('J', line*LCD_WIDTH + slice + i * 6 + 3, 14);
}

void lcdUpdate() {
    for (int i = 0; i < 4; i++) {
        uint8_t first = buffer[i*LCD_WIDTH];
        for (int j = 0; j < LCD_WIDTH - 1; j++) {
            buffer[i*LCD_WIDTH + j] = buffer[i*LCD_WIDTH + j + 1];
        }
        buffer[i*LCD_WIDTH + LCD_WIDTH - 1] = first;
    }
}
