#include "lcd.h"

void lcd_clear(uint8_t buffer[LCD_BUFFER_SIZE]) {
	// Sets each element of the buffer to 0xAA
	memset(buffer, 0xAA, LCD_BUFFER_SIZE);
	lcd_push_buffer(buffer);
}

void lcd_write_string(uint8_t buffer[LCD_BUFFER_SIZE], char * string) {
	uint8_t i, j;
	const char * charData;
	// Clear buffer
	memset(buffer, 0x00, LCD_BUFFER_SIZE);
	// Loop over each character in the string
	for (i = 0; string[i]; i++) {
		charData = character_data[string[i] - 0x20];
		for (j = 0; j < 5; j++) {
			buffer[i * 6 + j] = charData[j];
		}
	}
	lcd_push_buffer(buffer);
}

void lcd_update(uint8_t buffer[LCD_BUFFER_SIZE], char * string, uint32_t tick) {
	lcd_write_string(buffer, string);
}
