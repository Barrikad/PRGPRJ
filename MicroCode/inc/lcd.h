#include "30010_io.h"
#include "charset.h"
#include <string.h>

#ifndef LCD_H_
#define LCD_H_

void lcd_init(); // Re-export from 30010_io.h
void lcd_clear();
void lcd_write_string(char * string);
void lcd_update();

#endif /* LCD_H_ */
