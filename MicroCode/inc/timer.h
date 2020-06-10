#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h"
#include "stm32f30x.h"

void initTimer2(uint16_t prescaler, uint16_t reloadValue, void (*fun_ptr)());

void initTimer3(uint16_t prescaler, uint16_t reloadValue, void (*fun_ptr)());

void initTimer4(uint16_t prescaler, uint16_t reloadValue, void (*fun_ptr)());

void enableTimer2();
void enableTimer3();
void enableTimer4();

void disableTimer2();
void disableTimer3();
void disableTimer4();

#endif /* TIMER2_H_INCLUDED */
