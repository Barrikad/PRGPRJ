#include <stdint.h>

#ifndef LCD_H_
#define LCD_H_

#define LCD_WIDTH 128
#define LCD_HEIGHT 32

// Initialize the LCD.
void lcdInit();

// Clear the internal LCD buffer.
void lcdClear();

// Write a single pixel to the buffer at the location.
void lcdWritePixel(uint8_t x, uint8_t y);

// Clear a single pixel in the buffer at the location.
void lcdClearPixel(uint8_t x, uint8_t y);

// Write a character into the buffer at the location.
// TODO: Move this to API?
void lcdWriteChar(char chr, uint8_t x, uint8_t y);

// Flush the internal buffer to the LCD.
void lcdFlush();

#endif /* LCD_H_ */
