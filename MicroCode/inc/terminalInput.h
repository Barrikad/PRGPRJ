#ifndef TERMINALINPUT_H_INCLUDED
#define TERMINALINPUT_H_INCLUDED
#include <stdint.h>
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h"
#include "stm32f30x.h"

void readCharsInto(uint8_t numberOfChars, char* arr);

#endif /* TERMINALINPUT_H_INCLUDED */
