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
        default:
            return NULL;
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
        default:
            return 0;
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

void setOutput(int8_t pin, char port, int8_t on){
    GPIO_TypeDef *gpio = getGPIO(port);
    if(on){
        gpio->ODR &= ~(1 << pin);
    }
    else{
        gpio->ODR |= (1 << pin);
    }
}

void initJoystick(){
    initInput(4,'A'); //up
    initInput(0,'B'); //down
    initInput(5,'B'); //center
    initInput(0,'C'); //right
    initInput(1,'C'); //left
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

void initLed() {
    initOutput(4,'B'); //red
    initOutput(7,'C'); //green
    initOutput(9,'A'); //blue
}

void setLed(uint8_t color){
    if(color & 1){
        setOutput(9,'A',1);
    }
    else{
        setOutput(9,'A',0);
    }
    if(color & 2){
        setOutput(7,'C',1);
    }
    else{
        setOutput(7,'C',0);
    }
    if(color & 4){
        setOutput(4,'B',1);
    }
    else{
        setOutput(4,'B',0);
    }
}

void ledToJoystick(){
    uint8_t jsPosition = readJoystick();
    if(jsPosition & 1){ //up
        if(jsPosition & 8){ //center
            setLed(1 + 2);
        }
        else{
            setLed(1);
        }
    }
    else if(jsPosition & 2){ //down
        setLed(1 + 2 + 4);
    }
    else if(jsPosition & 4){ //left
        if(jsPosition & 8){ //center
            setLed(1 + 4);
        }
        else{
            setLed(2);
        }
    }
    else if(jsPosition & 16){ //right
        if(jsPosition & 8){ //center
            setLed(2 + 4);
        }
        else{
            setLed(4);
        }
    }
    else{
        setLed(0);
    }
}
