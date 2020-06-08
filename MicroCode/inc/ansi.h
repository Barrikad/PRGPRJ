#include <stdint.h>
#include <stdio.h>

#ifndef ANSI_H_INCLUDED
#define ANSI_H_INCLUDED

void fgcolor(uint8_t foreground);
void bgcolor(uint8_t background);
void color(uint8_t foreground, uint8_t background);
void clrscr();
void clreol();
void gotoxy(int8_t x, int8_t y);
void underline(int8_t on);
void blink(int8_t on);
void inverse(int8_t on);
void up(int8_t x);
void down(int8_t x);
void right(int8_t x);
void left(int8_t x);
void window(int8_t x1, int8_t y1, int8_t x2, int8_t y2, int8_t title[], int8_t style);
void printAnsi(int8_t ch, int reps);

#endif /* ANSI_H_INCLUDED */
