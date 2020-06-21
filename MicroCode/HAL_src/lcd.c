#include "lcd.h"
#include "30010_io.h"
#include "charset.h"
#include <string.h>

#define LCD_BUFFER_SIZE 512

// The internal buffer.
static uint8_t buffer[LCD_BUFFER_SIZE];

void lcdInit() {
    lcd_init();
}

void lcdClear() {
    memset(buffer, 0x00, LCD_BUFFER_SIZE);
}

void lcdWritePixel(uint8_t x, uint8_t y) {
    buffer[x + (y / 8) * LCD_WIDTH] |=  (0x01 << y);
}

void lcdClearPixel(uint8_t x, uint8_t y) {
    buffer[x + (y / 8) * LCD_WIDTH] &= ~(0x01 << y);
}

// Internal helper to write a vertical line to the buffer.
// TODO: Make this public?
static void lcdWriteVerticalLine(uint8_t line, uint8_t x, uint8_t y) {
    // TODO: Make `y` work properly here!
    buffer[x + (y / 8) * LCD_WIDTH] = line;
}

// TODO: Make `y` work properly in this.
void lcdWriteChar(char chr, uint8_t x, uint8_t y) {
    int8_t i;
    // Note: The character should be between 0x20 and 0x80
    const char * charData = character_data[chr - 0x20];
    for (i = 0; i < 5; i++) {
        lcdWriteVerticalLine(charData[i], x + i, y);
    }
}

void lcdAntiWriteChar(char chr, uint8_t x, uint8_t y) {
    int8_t i;
    // Note: The character should be between 0x20 and 0x80
    const char * charData = character_data[chr - 0x20];
    for (i = 0; i < 5; i++) {
        lcdWriteVerticalLine(~charData[i], x + i, y);
    }
    lcdWriteVerticalLine(0xFF, x + 5, y);
}

void lcdFlush() {
    lcd_push_buffer(buffer);
}
