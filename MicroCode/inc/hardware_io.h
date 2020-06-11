#include "stm32f30x.h"
#include <stdint.h>

#ifndef HARDWAREIO_H_INCLUDED
#define HARDWAREIO_H_INCLUDED

typedef struct {
	GPIO_TypeDef* gpio;
	int8_t pin;
	uint32_t rcc;
} gpio_pin_t;

extern const gpio_pin_t JOYSTICK_UP;
extern const gpio_pin_t JOYSTICK_DOWN;
extern const gpio_pin_t JOYSTICK_LEFT;
extern const gpio_pin_t JOYSTICK_RIGHT;
extern const gpio_pin_t JOYSTICK_MIDDLE;

extern const gpio_pin_t LED_RED;
extern const gpio_pin_t LED_GREEN;
extern const gpio_pin_t LED_BLUE;

void initInput(const gpio_pin_t gpio_pin);
void initOutput(const gpio_pin_t gpio_pin);

uint8_t getInput(const gpio_pin_t gpio_pin);
void setOutput(const gpio_pin_t gpio_pin, uint8_t on);

void initJoystick();
void initLeds();

void setLeds(uint8_t color);
uint8_t readJoystick();

void initLeds();

void setLeds(uint8_t color);

void ledToJoystick();

#endif /* HARDWAREIO_H_INCLUDED */
