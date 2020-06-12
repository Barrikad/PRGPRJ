#ifndef ANSI_H_INCLUDED
#define ANSI_H_INCLUDED

//Change foreground color. 16 choices (0-indexed)
void fgcolor(uint8_t foreground);

//Change background color. 8 choices (0-indexed)
void bgcolor(uint8_t background);

//change both background and foreground color
void color(uint8_t foreground, uint8_t background);

//clear screen. Not reliable for nonstandard terminal size
void clrscr();

//clear from cursor to end of line
void clreol();

//go to position x,y. x is width, y is height. 0-indexed
void gotoxy(int8_t x, int8_t y);

//underline newly written text
void underline(int8_t on);

//blink newly written text
void blink(int8_t on);

//inverse background and foreground color for newly written text
void inverse(int8_t on);

//go up x lines
void up(int8_t x);

//go down x lines
void down(int8_t x);

//go right x columns
void right(int8_t x);

//go left x columns
void left(int8_t x);

#endif /* ANSI_H_INCLUDED */
