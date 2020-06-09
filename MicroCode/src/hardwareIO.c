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
    gpio->MODER |= (0x00000000 << (2 * pin));

    gpio->PUPDR &= ~(0x00000003 << (2 * pin));
    gpio->PUPDR |= (0x00000002 << (2 * pin));
}

void initOutput(int8_t pin, char port){
    GPIO_TypeDef *gpio = getGPIO(port);

    RCC->AHBENR |= getRCCGPIO(port);

    gpio->OSPEEDR &= ~(0x00000003 << (pin * 2));
    gpio->OSPEEDR |= (0x00000002 << (pin * 2));

    gpio->OTYPER &= ~(0x0001 << (pin));
    gpio->OTYPER |= (0x0001 << (pin));

    gpio->MODER &= ~(0x00000003 << (pin * 2));
    gpio->MODER |= (0x00000001 << (pin * 2));
}

uint8_t getInput(int8_t pin, char port){
    GPIO_TypeDef *gpio = getGPIO(port);
    return (gpio->IDR & (0x0001 << pin)) >> pin;
}

void setOutput(int8_t pin, char port, int8_t value){
    GPIO_TypeDef *gpio = getGPIO(port);
    if(value){
        gpio->ODR |= (1 << pin);
    }
    else{
        gpio->ODR &= ~(1 << pin);
    }
}

void initJoystick(){
    initInput(4,'A');
    initInput(0,'B');
    initInput(5,'B');
    initInput(0,'C');
    initInput(1,'C');
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
