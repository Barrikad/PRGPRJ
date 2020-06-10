#ifndef TIMER2_H_INCLUDED
#define TIMER2_H_INCLUDED
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h"
#include "stm32f30x.h"

void initTimer2(uint16_t prescaler, uint16_t reloadValue, void (*fun_ptr)());

#endif /* TIMER2_H_INCLUDED */
