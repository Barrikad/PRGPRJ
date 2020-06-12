#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h"
#include "stm32f30x.h"
#include "hardware_io.h"

const gpio_pin_t JOYSTICK_UP     = { GPIOA, 4, RCC_AHBPeriph_GPIOA };
const gpio_pin_t JOYSTICK_DOWN   = { GPIOB, 0, RCC_AHBPeriph_GPIOB };
const gpio_pin_t JOYSTICK_LEFT   = { GPIOC, 1, RCC_AHBPeriph_GPIOC };
const gpio_pin_t JOYSTICK_RIGHT  = { GPIOC, 0, RCC_AHBPeriph_GPIOC };
const gpio_pin_t JOYSTICK_MIDDLE = { GPIOB, 5, RCC_AHBPeriph_GPIOB };

const gpio_pin_t LED_RED   = { GPIOB, 4, RCC_AHBPeriph_GPIOB };
const gpio_pin_t LED_GREEN = { GPIOC, 7, RCC_AHBPeriph_GPIOC };
const gpio_pin_t LED_BLUE  = { GPIOA, 9, RCC_AHBPeriph_GPIOA };

void initInput(const gpio_pin_t gpio_pin){
    RCC->AHBENR |= gpio_pin.rcc;

    gpio_pin.gpio->MODER &= ~(0x00000003 << (2 * gpio_pin.pin)); // Clear mode register
    gpio_pin.gpio->MODER |=  (0x00000000 << (2 * gpio_pin.pin)); // Set mode register to input
    gpio_pin.gpio->PUPDR &= ~(0x00000003 << (2 * gpio_pin.pin)); // Clear push/pull register
    gpio_pin.gpio->PUPDR |=  (0x00000002 << (2 * gpio_pin.pin)); // Set push/pull register to pull-down
}

void initOutput(const gpio_pin_t gpio_pin){
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

uint8_t getInput(const gpio_pin_t gpio_pin){
    return (gpio_pin.gpio->IDR & (0x0001 << gpio_pin.pin)) >> gpio_pin.pin;
}

// Set the value on the given GPIO / pin
void setOutput(const gpio_pin_t gpio_pin, uint8_t on){
    if(on){
    	gpio_pin.gpio->ODR |= (1 << gpio_pin.pin);
    }
    else{
    	gpio_pin.gpio->ODR &= ~(1 << gpio_pin.pin);
    }
}

void initJoystick() {
    initInput(JOYSTICK_UP);
    initInput(JOYSTICK_DOWN);
    initInput(JOYSTICK_LEFT);
    initInput(JOYSTICK_RIGHT);
    initInput(JOYSTICK_MIDDLE);

}

void initLeds() {
	initOutput(LED_RED);
	initOutput(LED_GREEN);
	initOutput(LED_BLUE);
}


uint8_t readJoystick() {
	uint8_t rtn = 0;
	rtn |= getInput(JOYSTICK_UP)     << 0;
	rtn |= getInput(JOYSTICK_DOWN)   << 1;
	rtn |= getInput(JOYSTICK_LEFT)   << 2;
	rtn |= getInput(JOYSTICK_RIGHT)  << 3;
    rtn |= getInput(JOYSTICK_MIDDLE) << 4;
	return rtn;
}


// Set the leds, based on the given color
// The first bit sets a red LED, the second bit a green LED and the third bit a blue LED.
void setLeds(uint8_t color) {
	// The values are inverted, since the LEDs are pull-down
	setOutput(LED_RED, !(color & 0x01));
	setOutput(LED_GREEN, !(color & 0x02));
	setOutput(LED_BLUE, !(color & 0x04));
}

void ledToJoystick(){
    uint8_t jsPosition = readJoystick();
    if(jsPosition & 1){ //up
        if(jsPosition & 16){ //center
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
        if(jsPosition & 16){ //center
            setLeds(1 + 4);
        }
        else{
            setLeds(2);
        }
    }
    else if(jsPosition & 8){ //right
        if(jsPosition & 16){ //center
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
