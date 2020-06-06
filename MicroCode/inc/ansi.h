#include <stdint.h>
#include <stdio.h>

#ifndef ANSI_H_INCLUDED
#define ANSI_H_INCLUDED

void fgcolor(uint8_t foreground);
void bgcolor(uint8_t background);
void color(uint8_t foreground, uint8_t background);
void clrscr();
void clreol();
void gotoxy(char x, char y);
void underline(char on);
void blink(char on);
void inverse(char on);
void up(char x);
void down(char x);
void right(char x);
void left(char x);
void window(char x1, char y1, char x2, char y2, char title[], char style);
void printAnsi(char ch, int reps);

#endif /* ANSI_H_INCLUDED */
