#include <stdio.h>
#include "ansi.h"

//Escape character
#define ESC 0x1B

//Single line
#define CORNER_TL_S 208 + 10 //top left corner
#define CORNER_TR_S 176 + 15
#define CORNER_BL_S 192 + 0
#define CORNER_BR_S 208 + 9
#define BAR_V_S 176 + 3 //Vertical bar
#define BAR_H_S 192 + 4
#define CROSS_L_S 176 + 4 //Cross pointing left
#define CROSS_R_S 192 + 3
#define CROSS_U_S 192 + 1
#define CROSS_D_S 192 + 2
#define CROSS_A_S 192 + 5 //full cross (A for All)

//Double line
#define CORNER_TL_D 192 + 9 //top left corner
#define CORNER_TR_D 176 + 11
#define CORNER_BL_D 192 + 8
#define CORNER_BR_D 176 + 12
#define BAR_V_D 176 + 10 //Vertical bar
#define BAR_H_D 192 + 13
#define CROSS_L_D 176 + 9 //cross pointing left
#define CROSS_R_D 192 + 12
#define CROSS_U_D 192 + 10
#define CROSS_D_D 192 + 11
#define CROSS_A_D 192 + 14 //full cross (A for All)

#define space 32

void fgcolor(uint8_t foreground) {
/*  Value      foreground     Value     foreground
    ------------------------------------------------
      0        Black            8       Dark Gray
      1        Red              9       Light Red
      2        Green           10       Light Green
      3        Brown           11       Yellow
      4        Blue            12       Light Blue
      5        Purple          13       Light Purple
      6        Cyan            14       Light Cyan
      7        Light Gray      15       White
*/
  uint8_t type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%dm", ESC, type, foreground+30);
}

void bgcolor(uint8_t background) {
/* IMPORTANT:   When you first use this function you cannot get back to true white background in HyperTerminal.
   Why is that? Because ANSI does not support true white background (ANSI white is gray to most human eyes).
                The designers of HyperTerminal, however, preferred black text on white background, which is why
                the colors are initially like that, but when the background color is first changed there is no
 	              way comming back.
   Hint:        Use resetbgcolor(); clrscr(); to force HyperTerminal into gray text on black background.

    Value      Color
    ------------------
      0        Black
      1        Red
      2        Green
      3        Brown
      4        Blue
      5        Purple
      6        Cyan
      7        Gray
*/
  printf("%c[%dm", ESC, background+40);
}

void color(uint8_t foreground, uint8_t background) {
// combination of fgcolor() and bgcolor() - uses less bandwidth
  uint8_t type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%d;%dm", ESC, type, foreground+30, background+40);
}

void resetbgcolor() {
// gray on black text, no underline, no blink, no reverse
  printf("%c[m", ESC);
}

//Description of following functions in header file
//They are all aliases for simple ansi commands
void clrscr() {
    printf("%c[2J", ESC);
}
void clreol() {
    printf("%c[K", ESC);
}
void cursorHide() {
    printf("\x1b[?25l");
}
void cursorShow() {
    printf("\x1b[?25h");
}
void cursorToXY(int8_t x, int8_t y) {
    printf("%c[%d;%dH", ESC, y + 1, x + 1);
}
void cursorUp(int8_t x) {
    printf("%c[%dA", ESC, x);
}
void cursorDown(int8_t x) {
    printf("%c[%dB", ESC, x);
}
void cursorRight(int8_t x) {
    printf("%c[%dC", ESC, x);
}
void cursorLeft(int8_t x) {
    printf("%c[%dD", ESC, x);
}
void underline(int8_t on) {
    printf("%c[%dm", ESC, on ? 4 : 24);
}
void blink(int8_t on) {
    printf("%c[%dm", ESC, on ? 5 : 25);
}
void inverse(int8_t on) {
    printf("%c[%dm", ESC, on ? 7 : 27);
}

void printFix(int32_t i) {
 // Prints a signed 16.16 fixed point number
 if ((i & 0x80000000) != 0) { // Handle negative numbers
 printf("-");
 i = ~i + 1;
 }
 printf("%ld.%04ld", i >> 16, 10000 * (uint32_t)(i & 0xFFFF) >> 16);
 // Print a maximum of 4 decimal digits to avoid overflow
 }

