#include <stdint.h>
#include "30010_io.h"
#include "stm32f30x.h"
#include "led.h"
#include "pins.h"


void initLed(const gpio_pin_t gpio_pin){
    // Ensure GPIO is enabled
    RCC->AHBENR |= gpio_pin.rcc;

    // Configure pin as output
    gpio_pin.gpio->OSPEEDR &= ~(0x00000003 << (2 * gpio_pin.pin)); // Clear speed register
    gpio_pin.gpio->OSPEEDR |=  (0x00000002 << (2 * gpio_pin.pin)); // Set speed register (0x01 - 10 MHz, 0x02 - 2 MHz, 0x03 - 50 MHz)
    gpio_pin.gpio->OTYPER  &= ~(0x0001 << gpio_pin.pin);           // Clear output type register
    gpio_pin.gpio->OTYPER  |=  (0x0001 << gpio_pin.pin);           // Set output type register (0x00 - Push pull, 0x01 - Open drain)
    gpio_pin.gpio->MODER   &= ~(0x00000003 << (2 * gpio_pin.pin)); // Clear mode register
    gpio_pin.gpio->MODER   |=  (0x00000001 << (2 * gpio_pin.pin)); // Set mode register to output
}

void initLeds() {
	initLed(LED_RED);
	initLed(LED_GREEN);
	initLed(LED_BLUE);
}

void setLed(const gpio_pin_t gpio_pin){
    // Inverted since the LED are off when their respective bit value is 1.
    	gpio_pin.gpio->ODR &= ~(1 << gpio_pin.pin);

}

void clearLed(const gpio_pin_t gpio_pin){
    // Inverted since the LED are off when their respective bit value is 1.
    	gpio_pin.gpio->ODR |= (1 << gpio_pin.pin);
}




