#ifndef PINS_H_INCLUDED
#define PINS_H_INCLUDED

typedef struct {
	GPIO_TypeDef* gpio;
	int8_t pin;
	uint32_t rcc;
} gpio_pin_t;

#endif /* PINS_H_INCLUDED */
