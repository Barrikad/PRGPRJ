#ifndef LED_H_INCLUDED
#define LED_H_INCLUDED

#include "pins.h"

extern const gpio_pin_t LED_RED;
extern const gpio_pin_t LED_GREEN;
extern const gpio_pin_t LED_BLUE;


// Initializes LED, must be run before LED can be used.
void initLeds();



void setLed(const gpio_pin_t gpio_pin);


void clearLed(const gpio_pin_t gpio_pin);


#endif /* LED_H_INCLUDED */
