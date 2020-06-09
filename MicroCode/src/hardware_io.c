#include "hardware_io.h"

// Configure the given GPIO / pin as an input.
// Remember to enable the GPIO first!
void setPinAsInput(GPIO_TypeDef *gpio, uint8_t pin) {
	gpio->MODER &= ~(0x00000003 << (pin * 2)); // Clear mode register
	gpio->MODER |=  (0x00000000 << (pin * 2)); // Set mode register to input
	gpio->PUPDR &= ~(0x00000003 << (pin * 2)); // Clear push/pull register
	gpio->PUPDR |=  (0x00000002 << (pin * 2)); // Set push/pull register to pull-down
}

// Read from the given GPIO / pin.
// Returns whether or not the pin is asserted.
uint8_t getPinValue(GPIO_TypeDef *gpio, uint8_t pin) {
	return gpio->IDR & (0x0001 << pin) ? 1 : 0;
}

void setupHardwareIO() {
	// Enable GPIO A, B and C
	RCC->AHBENR |= RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC;

	setPinAsInput(GPIOA, 4); // Up
	setPinAsInput(GPIOB, 0); // Down
	setPinAsInput(GPIOC, 1); // Left
	setPinAsInput(GPIOB, 5); // Center
	setPinAsInput(GPIOC, 0); // Right
}

uint8_t readJoystick() {
	uint8_t rtn = 0;
	rtn |= getPinValue(GPIOA, 4) << 0; // Up
	rtn |= getPinValue(GPIOB, 0) << 1; // Down
	rtn |= getPinValue(GPIOC, 1) << 2; // Left
	rtn |= getPinValue(GPIOB, 5) << 3; // Center
	rtn |= getPinValue(GPIOC, 0) << 4; // Right
	return rtn;
}

void printJoystick(uint8_t joystick) {
	// If, and not switch, since multiple directions can be active!
	if (joystick & 0x01) {
		printf("Up ");
	}
	if (joystick & 0x02) {
		printf("Down ");
	}
	if (joystick & 0x04) {
		printf("Left ");
	}
	if (joystick & 0x08) {
		printf("Center ");
	}
	if (joystick & 0x10) {
		printf("Right ");
	}
	printf("\n");
}
