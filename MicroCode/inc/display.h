#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED
#include <stdint.h>
#include <string.h>
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h"
#include "stm32f30x.h"
#include "charset.h"

void initDisplay();

void lcdWriteString(char str[], uint8_t line, uint8_t slice);

void setFlag();

void lcdUpdate();

#endif /* DISPLAY_H_INCLUDED */
