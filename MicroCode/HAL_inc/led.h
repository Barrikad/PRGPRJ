#ifndef LED_H_INCLUDED
#define LED_H_INCLUDED

#include "pins.h"

const gpio_pin_t LED_RED   = { GPIOB, 4, RCC_AHBPeriph_GPIOB };
const gpio_pin_t LED_GREEN = { GPIOC, 7, RCC_AHBPeriph_GPIOC };
const gpio_pin_t LED_BLUE  = { GPIOA, 9, RCC_AHBPeriph_GPIOA };


// Initializes LED, must be run before LED can be used.
void initLeds();



void setLed(const gpio_pin_t gpio_pin);


void clearLed(const gpio_pin_t gpio_pin);


#endif /* LED_H_INCLUDED */
