#include "lcd.h"
#include "30010_io.h"
#include "charset.h"
#include <assert.h>
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
    assert(x < LCD_WIDTH);
    assert(y < LCD_HEIGHT);
    buffer[x + (y / 8) * LCD_WIDTH] |=  (0x01 << y);
}

void lcdClearPixel(uint8_t x, uint8_t y) {
    assert(x < LCD_WIDTH);
    assert(y < LCD_HEIGHT);
    buffer[x + (y / 8) * LCD_WIDTH] &= ~(0x01 << y);
}

// Internal helper to write a vertical line to the buffer.
// TODO: Make this public?
static void lcdWriteVerticalLine(uint8_t line, uint8_t x, uint8_t y) {
    assert(x < LCD_WIDTH);
    assert(y < LCD_HEIGHT);
    // TODO: Make `y` work properly here!
    buffer[x + (y / 8) * LCD_WIDTH] = line;
}

// TODO: Make `y` work properly in this.
void lcdWriteChar(char chr, uint8_t x, uint8_t y) {
    int8_t i;
    const char * charData;
    assert(chr >= 0x20 && chr < 0x80);

    charData = character_data[chr - 0x20];
    for (i = 0; i < 5; i++) {
        lcdWriteVerticalLine(charData[i], x + i, y);
    }
}

void lcdFlush() {
    lcd_push_buffer(buffer);
}
