#include "hardwareIO.h"

GPIO_TypeDef* getGPIO(char port){
    switch(port){
        case 'A':
            return GPIOA;
        case 'B':
            return GPIOB;
        case 'C':
            return GPIOC;
        case 'D':
            return GPIOD;
        case 'E':
            return GPIOE;
    }
}

uint32_t getRCCGPIO(char port){
    switch(port){
        case 'A':
            return RCC_AHBPeriph_GPIOA;
        case 'B':
            return RCC_AHBPeriph_GPIOB;
        case 'C':
            return RCC_AHBPeriph_GPIOC;
        case 'D':
            return RCC_AHBPeriph_GPIOD;
        case 'E':
            return RCC_AHBPeriph_GPIOE;
    }
}

void initInput(int8_t pin, char port){
    GPIO_TypeDef *gpio = getGPIO(port);

    RCC->AHBENR |= getRCCGPIO(port);

    gpio->MODER &= ~(0x00000003 << (2 * pin));
    gpio->MODER |=  (0x00000000 << (2 * pin));
	gpio->PUPDR &= ~(0x00000003 << (2 * pin)); // Clear push/pull register
	gpio->PUPDR |=  (0x00000002 << (2 * pin)); // Set push/pull register to pull-down
}

void initOutput(int8_t pin, char port){
    GPIO_TypeDef *gpio = getGPIO(port);

    // Ensure GPIO is enabled
    RCC->AHBENR |= getRCCGPIO(port);

    // Configure pin as output
    gpio->OSPEEDR &= ~(0x00000003 << (2 * pin)); // Clear speed register
    gpio->OSPEEDR |=  (0x00000002 << (2 * pin)); // Set speed register (0x01 - 10 MHz, 0x02 - 2 MHz, 0x03 - 50 MHz)
    gpio->OTYPER  &= ~(0x0001 << pin);           // Clear output type register
    gpio->OTYPER  |=  (0x0001 << pin);           // Set output type register (0x00 - Push pull, 0x01 - Open drain)
    gpio->MODER   &= ~(0x00000003 << (2 * pin)); // Clear mode register
    gpio->MODER   |=  (0x00000001 << (2 * pin)); // Set mode register to output
}

uint8_t getInput(int8_t pin, char port){
    GPIO_TypeDef *gpio = getGPIO(port);
    return (gpio->IDR & (0x0001 << pin)) >> pin;
}

// Set the value on the given GPIO / pin
void setOutput(int8_t pin, char port, uint8_t value){
    GPIO_TypeDef *gpio = getGPIO(port);
    if (value) {
        gpio->ODR |= (0x0001 << pin); // Set pin
    } else {
        gpio->ODR &= ~(0x0001 << pin); // Clear pin
    }
}

void initJoystick() {
    initInput(4, 'A'); // Up
    initInput(0, 'B'); // Down
    initInput(5, 'B'); // Left
    initInput(0, 'C'); // Center
    initInput(1, 'C'); // Right
}

uint8_t readJoystick() {
	uint8_t rtn = 0;
	rtn |= getInput(4,'A') << 0; // Up
	rtn |= getInput(0,'B') << 1; // Down
	rtn |= getInput(1, 'C') << 2; // Left
	rtn |= getInput(5, 'B') << 3; // Center
	rtn |= getInput(0, 'C') << 4; // Right
	return rtn;
}
