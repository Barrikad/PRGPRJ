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

void setInput(int8_t pin, char port){
    GPIO_TypeDef *gpio = getGPIO(port);

    RCC->AHBENR |= getRCCGPIO(port);

    gpio->MODER &= ~(0x00000003 << (2 * pin));
    gpio->MODER |= (0x00000000 << (2 * pin));

    gpio->PUPDR &= ~(0x00000003 << (2 * pin));
    gpio->PUPDR |= (0x00000002 << (2 * pin));
}

uint8_t getInput(int8_t pin, char port){
    GPIO_TypeDef *gpio = getGPIO(port);
    return (gpio->IDR & (0x0001 << pin)) >> pin;
}

void initJoystick(){
    setInput(4,'A');
    setInput(0,'B');
    setInput(5,'B');
    setInput(0,'C');
    setInput(1,'C');
}

uint8_t readJoystick(){
    uint8_t up = getInput(4,'A');
    uint8_t right = getInput(0,'C');
    uint8_t down = getInput(0,'B');
    uint8_t left = getInput(1,'C');
    uint8_t in = getInput(5,'B');

    return up + 2*down + 4*left + 8*right + 16*in;
}
