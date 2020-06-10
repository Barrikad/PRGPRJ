#include "lcd.h"

#define BUFFER_SIZE 512

void lcd_clear() {
	uint8_t buffer[BUFFER_SIZE];
	// Sets each element of the buffer to 0xAA
	memset(buffer, 0xAA, BUFFER_SIZE);
	lcd_push_buffer(buffer);
}

void lcd_write_string(char * string) {
	uint8_t i, j;
	const char * charData;
	uint8_t buffer[BUFFER_SIZE];
	// Clear buffer
	memset(buffer, 0x00, BUFFER_SIZE);
	// Loop over each character in the string
	for (i = 0; string[i]; i++) {
		charData = character_data[string[i] - 0x20];
		for (j = 0; j < 5; j++) {
			buffer[i * 6 + j] = charData[j];
		}
	}
	lcd_push_buffer(buffer);
}

void lcd_update() {

}
