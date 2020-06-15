#ifndef PINS_H_INCLUDED
#define PINS_H_INCLUDED
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h"
#include "stm32f30x.h"

typedef struct {
	GPIO_TypeDef* gpio;
	int8_t pin;
	uint32_t rcc;
} gpio_pin_t;

#endif /* PINS_H_INCLUDED */
