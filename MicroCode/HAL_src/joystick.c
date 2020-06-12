#include <stdint.h>
#include "30010_io.h"
#include "stm32f30x.h"
#include "joystick.h"

//Pins, ports, and rcc for the different joystick positions
const gpio_pin_t JOYSTICK_UP     = { GPIOA, 4, RCC_AHBPeriph_GPIOA };
const gpio_pin_t JOYSTICK_DOWN   = { GPIOB, 0, RCC_AHBPeriph_GPIOB };
const gpio_pin_t JOYSTICK_LEFT   = { GPIOC, 1, RCC_AHBPeriph_GPIOC };
const gpio_pin_t JOYSTICK_RIGHT  = { GPIOC, 0, RCC_AHBPeriph_GPIOC };
const gpio_pin_t JOYSTICK_MIDDLE = { GPIOB, 5, RCC_AHBPeriph_GPIOB };

//Initialize a pin to binary input
void initButton(const gpio_pin_t gpio_pin){
    RCC->AHBENR |= gpio_pin.rcc;

    gpio_pin.gpio->MODER &= ~(0x00000003 << (2 * gpio_pin.pin)); // Clear mode register
    gpio_pin.gpio->MODER |=  (0x00000000 << (2 * gpio_pin.pin)); // Set mode register to input
    gpio_pin.gpio->PUPDR &= ~(0x00000003 << (2 * gpio_pin.pin)); // Clear push/pull register
    gpio_pin.gpio->PUPDR |=  (0x00000002 << (2 * gpio_pin.pin)); // Set push/pull register to pull-down
}

//Returns 1 if pin is HIGH, and 0 if LOW
uint8_t buttonIsPressed(const gpio_pin_t gpio_pin){
    //Checks the value of the given pin, and reduces the result to 0 or 1
    return (gpio_pin.gpio->IDR & (0x0001 << gpio_pin.pin)) >> gpio_pin.pin;
}

//Initialize all joystick-positions as buttons
void initJoystick(){
    initButton(JOYSTICK_UP);
    initButton(JOYSTICK_DOWN);
    initButton(JOYSTICK_LEFT);
    initButton(JOYSTICK_RIGHT);
    initButton(JOYSTICK_MIDDLE);
}

//Returns a byte reflecting joystick position. Bit values explained in header
uint8_t readJoystick(const gpio_pin_t gpio_pin) {
	return buttonIsPressed(gpio_pin);
}
