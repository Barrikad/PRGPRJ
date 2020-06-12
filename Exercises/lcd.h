#include <stdint.h>

#ifndef LCD_H_
#define LCD_H_

void lcdInit();
void lcdFlush();
void lcdClear();
void lcdWriteString(char str[], uint8_t line, uint8_t slice);
void lcdUpdate();

#endif /* LCD_H_ */
