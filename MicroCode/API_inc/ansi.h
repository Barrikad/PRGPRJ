#include <stdint.h>

#ifndef ANSI_H_INCLUDED
#define ANSI_H_INCLUDED

//Change foreground color. 16 choices (0-indexed)
void fgcolor(uint8_t foreground);

//Change background color. 8 choices (0-indexed)
void bgcolor(uint8_t background);

//change both background and foreground color
void color(uint8_t foreground, uint8_t background);

void resetcolor();

//clear screen. Not reliable for nonstandard terminal size
void clrscr();

//clear from cursor to end of line
void clreol();

// Hide the cursor. Some terminals might not support this.
void cursorHide();

// Show the cursor again. Some terminals might not support this.
void cursorShow();

//go to position x,y. x is width, y is height. 0-indexed
void cursorToXY(uint8_t x, uint8_t y);

//underline newly written text
void underline(uint8_t on);

//blink newly written text
void blink(uint8_t on);

//inverse background and foreground color for newly written text
void inverse(uint8_t on);

//go up x lines
void cursorUp(uint8_t x);

//go down x lines
void cursorDown(uint8_t x);

//go right x columns
void cursorRight(uint8_t x);

//go left x columns
void cursorLeft(uint8_t x);

void printFix(int32_t i);


#endif /* ANSI_H_INCLUDED */
