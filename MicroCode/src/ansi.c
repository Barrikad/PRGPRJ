#define ESC 0x1B
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "charset.h"

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

void gotoxy(char x, char y) {
    printf("%c[%d;%dH", ESC, x, y);
}

void up(char x) {
    printf("%c[%dA", ESC, x);
}

void down(char x) {
    printf("%c[%dB", ESC, x);
}

void right(char x) {
    printf("%c[%dC", ESC, x);
}

void left(char x) {
    printf("%c[%dD", ESC, x);
}

void underline(char on) {
    printf("%c[%dm", ESC, on ? 4 : 24);
}

void blink(char on) {
    printf("%c[%dm", ESC, on ? 5 : 25);
}

void inverse(char on) {
    printf("%c[%dm", ESC, on ? 7 : 27);
}

//THIS SHOULD PROLLY BE MOVED
int strln(char str[]) {
    int index = 0;
    while(str[index] != '\0') {
        index++;
    }
    return index;
}

void printAnsi(char ch, int reps) {
    for(int i = 0; i < reps; i++){
        printf("\%c",ch);
    }
}


void window(char x1, char y1, char x2, char y2, char title[], char style) {
    char height = x2 - x1 + 1; //width is inclusive
    char width = y2 - y1 + 1;
    char titleLength = strln(title);

    char cornerTL;
    char cornerTR;
    char cornerBL;
    char cornerBR;
    char barH;
    char barV;
    char titleStart;
    char titleEnd;
    switch(style){
        case 0 :
            cornerTL = corner_TL_S;
            cornerTR = corner_TR_S;
            cornerBL = corner_BL_S;
            cornerBR = corner_BR_S;
            barH = bar_H_S;
            barV = bar_V_S;
            titleStart = cross_L_S;
            titleEnd = cross_R_S;
            break;
        case 1 :
            cornerTL = corner_TL_D;
            cornerTR = corner_TR_D;
            cornerBL = corner_BL_D;
            cornerBR = corner_BR_D;
            barH = bar_H_D;
            barV = bar_V_D;
            titleStart = cross_L_D;
            titleEnd = cross_R_D;
            break;
    }

    gotoxy(x1,0);
    printf("\n");
    right(y1-1);
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
    for(int i = 1; i < height - 1; i++) {
        right(y1-1);
        printAnsi(barV,1);
        printAnsi(space,width - 2);
        printAnsi(barV,1);
        printf("\n");
    }
    right(y1-1);
    printAnsi(cornerBL,1);
    printAnsi(barH,width - 2);
    printAnsi(cornerBR,1);
    printf("\n");
}
