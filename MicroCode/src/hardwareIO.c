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
void setOutput(int8_t pin, char port, uint8_t on){
    GPIO_TypeDef *gpio = getGPIO(port);
    if(on){
        gpio->ODR |= (1 << pin);
    }
    else{
        gpio->ODR &= ~(1 << pin);
    }
}

void initJoystick() {
    initInput(4, 'A'); // Up
    initInput(0, 'B'); // Down
    initInput(1, 'C'); // Left
    initInput(5, 'B'); // Center
    initInput(0, 'C'); // Right

}

void initLeds() {
	initOutput(4, 'B'); // Red
	initOutput(7, 'C'); // Green
	initOutput(9, 'A'); // Blue
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


// Set the leds, based on the given color
// The first bit sets a red LED, the second bit a green LED and the third bit a blue LED.
void setLeds(uint8_t color) {
	// The values are inverted, since the LEDs are pull-down
	setOutput(4, 'B', !(color & 0x01)); // Red
	setOutput(7, 'C', !(color & 0x02)); // Green
	setOutput(9, 'A', !(color & 0x04)); // Blue
}

void ledToJoystick(){
    uint8_t jsPosition = readJoystick();
    if(jsPosition & 1){ //up
        if(jsPosition & 8){ //center
            setLeds(1 + 2);
        }
        else{
            setLeds(1);
        }
    }
    else if(jsPosition & 2){ //down
        setLeds(1 + 2 + 4);
    }
    else if(jsPosition & 4){ //left
        if(jsPosition & 8){ //center
            setLeds(1 + 4);
        }
        else{
            setLeds(2);
        }
    }
    else if(jsPosition & 16){ //right
        if(jsPosition & 8){ //center
            setLeds(2 + 4);
        }
        else{
            setLeds(4);
        }
    }
    else{
        setLeds(0);
    }
}
