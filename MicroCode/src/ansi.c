#define ESC 0x1B
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "charset.h"
#include "project_utilities.h"

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

void clrscr() {
    printf("%c[2J", ESC);
}

void clreol() {
    printf("%c[K", ESC);
}

void gotoxy(int8_t x, int8_t y) {
    printf("%c[%d;%dH", ESC, y + 1, x + 1);
}

void up(int8_t x) {
    printf("%c[%dA", ESC, x);
}

void down(int8_t x) {
    printf("%c[%dB", ESC, x);
}

void right(int8_t x) {
    printf("%c[%dC", ESC, x);
}

void left(int8_t x) {
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

void printAnsi(int8_t ch, int16_t reps) {
    for(int16_t i = 0; i < reps; i++){
        printf("\%c",ch);
    }
}


void window(int8_t x1, int8_t y1, int8_t x2, int8_t y2, char title[], int8_t style) {
    int8_t height = y2 - y1 + 1; //width is inclusive
    int8_t width = x2 - x1 + 1;
    int16_t titleLength = strln(title);

    int8_t cornerTL;
    int8_t cornerTR;
    int8_t cornerBL;
    int8_t cornerBR;
    int8_t barH;
    int8_t barV;
    int8_t titleStart;
    int8_t titleEnd;
    switch(style){
        case 0 :
            cornerTL = CORNER_TL_S;
            cornerTR = CORNER_TR_S;
            cornerBL = CORNER_BL_S;
            cornerBR = CORNER_BR_S;
            barH = BAR_H_S;
            barV = BAR_V_S;
            titleStart = CROSS_L_S;
            titleEnd = CROSS_R_S;
            break;
        case 1 :
            cornerTL = CORNER_TL_D;
            cornerTR = CORNER_TR_D;
            cornerBL = CORNER_BL_D;
            cornerBR = CORNER_BR_D;
            barH = BAR_H_D;
            barV = BAR_V_D;
            titleStart = CROSS_L_D;
            titleEnd = CROSS_R_D;
            break;
    }

    gotoxy(0,y1);
    printf("\n");
    right(x1-1);
    printAnsi(cornerTL,1);
    printAnsi(barH,1);
    printAnsi(titleStart,1);
    inverse(1);
    printf("%s",title);
    inverse(0);
    printAnsi(titleEnd,1);
    printAnsi(barH,width - 5 - titleLength);
    printAnsi(cornerTR,1);
    printf("\n");
    for(int16_t i = 1; i < height - 1; i++) {
        right(x1-1);
        printAnsi(barV,1);
        printAnsi(space,width - 2);
        printAnsi(barV,1);
        printf("\n");
    }
    right(x1-1);
    printAnsi(cornerBL,1);
    printAnsi(barH,width - 2);
    printAnsi(cornerBR,1);
    printf("\n");
    gotoxy(0,0);
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

void walls(int8_t x1, int8_t y1, int8_t x2, int8_t y2){
    int8_t width = x2 - x1 - 1;
    int8_t height = y2 - y1 - 1;
    gotoxy(x1,y1);
    printAnsi(CORNER_TL_S,1);
    printAnsi(BAR_H_S,width);
    printAnsi(CORNER_TR_S,1);
    for(int i = 1; i <= height; i++){
        gotoxy(x1, y1 + i);
        printAnsi(BAR_V_S,1);
        right(width);
        printAnsi(BAR_V_S,1);
    }
    gotoxy(x1,y2);
    printAnsi(CORNER_BL_S,1);
    printAnsi(BAR_H_S,width);
    printAnsi(CORNER_BR_S,1);
}

void printJoystick(uint8_t joystick) {
	// If, and not switch, since multiple directions can be active!
	if (joystick & 0x01) {
		printf("Up ");
	}
	if (joystick & 0x02) {
		printf("Down ");
	}
	if (joystick & 0x04) {
		printf("Left ");
	}
	if (joystick & 0x08) {
		printf("Center ");
	}
	if (joystick & 0x10) {
		printf("Right ");
	}
	printf("\n");
}
