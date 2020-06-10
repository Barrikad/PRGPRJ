#include "30010_io.h"
#include "charset.h"
#include <string.h>

#ifndef LCD_H_
#define LCD_H_

#define LCD_BUFFER_SIZE 512

void lcd_init(); // Re-export from 30010_io.h
void lcd_clear(uint8_t buffer[LCD_BUFFER_SIZE]);
void lcd_write_string(uint8_t buffer[LCD_BUFFER_SIZE], char * string);
void lcd_update(uint8_t buffer[LCD_BUFFER_SIZE], char * string, uint32_t tick);

#endif /* LCD_H_ */
