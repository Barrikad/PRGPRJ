#include "boss_mode.h"
#include "ansi.h"
#include "keyboard.h"
#include "game.h"
#include "30010_io.h"
#include <stdio.h>

#define BOSS_MODE_CODE_LENGTH 1610
#define BOSS_MODE_STEP 3

// Code taken from joystick.c, and spaces converted to tabs
static const char bossModeCode[BOSS_MODE_CODE_LENGTH + 1] =
    "#include <stdint.h>\n"
    "#include \"30010_io.h\"\n"
    "#include \"stm32f30x.h\"\n"
    "#include \"joystick.h\"\n"
    "\n"
    "//Pins, ports, and rcc for the different joystick positions\n"
    "const gpio_pin_t JOYSTICK_UP     = { GPIOA, 4, RCC_AHBPeriph_GPIOA };\n"
    "const gpio_pin_t JOYSTICK_DOWN   = { GPIOB, 0, RCC_AHBPeriph_GPIOB };\n"
    "const gpio_pin_t JOYSTICK_LEFT   = { GPIOC, 1, RCC_AHBPeriph_GPIOC };\n"
    "const gpio_pin_t JOYSTICK_RIGHT  = { GPIOC, 0, RCC_AHBPeriph_GPIOC };\n"
    "const gpio_pin_t JOYSTICK_MIDDLE = { GPIOB, 5, RCC_AHBPeriph_GPIOB };\n"
    "\n"
    "//Initialize a pin to binary input\n"
    "static void initButton(const gpio_pin_t gpio_pin){\n"
    "\tRCC->AHBENR |= gpio_pin.rcc;\n"
    "\n"
    "\tgpio_pin.gpio->MODER &= ~(0x00000003 << (2 * gpio_pin.pin)); // Clear mode register\n"
    "\tgpio_pin.gpio->MODER |=  (0x00000000 << (2 * gpio_pin.pin)); // Set mode register to input\n"
    "\tgpio_pin.gpio->PUPDR &= ~(0x00000003 << (2 * gpio_pin.pin)); // Clear push/pull register\n"
    "\tgpio_pin.gpio->PUPDR |=  (0x00000002 << (2 * gpio_pin.pin)); // Set push/pull register to pull-down\n"
    "}\n"
    "\n"
    "//Returns 1 if pin is HIGH, and 0 if LOW\n"
    "static uint8_t buttonIsPressed(const gpio_pin_t gpio_pin){\n"
    "\t//Checks the value of the given pin, and reduces the result to 0 or 1\n"
    "\treturn (gpio_pin.gpio->IDR & (0x0001 << gpio_pin.pin)) >> gpio_pin.pin;\n"
    "}\n"
    "\n"
    "//Initialize all joystick-positions as buttons\n"
    "void initJoystick(){\n"
    "\tinitButton(JOYSTICK_UP);\n"
    "\tinitButton(JOYSTICK_DOWN);\n"
    "\tinitButton(JOYSTICK_LEFT);\n"
    "\tinitButton(JOYSTICK_RIGHT);\n"
    "\tinitButton(JOYSTICK_MIDDLE);\n"
    "}\n"
    "\n"
    "//Returns a byte reflecting joystick position. Bit values explained in header\n"
    "uint8_t readJoystick(const gpio_pin_t gpio_pin) {\n"
    "\treturn buttonIsPressed(gpio_pin);\n"
    "}\n";

static uint16_t currentPosition;

void initBossMode() {
    clearKeys();
    cursorToXY(0, 0);
    cursorShow();
    color(2, 0); // Green text, black background
    clrscr();
    currentPosition = 0;
}

uint8_t processBossMode() {
    uint8_t i;
    uint8_t c = uart_get_char();
    if (!c) {
        return 0;
    }
    if (c == SPACE) {
        // Exit boss mode
        return 1;
    }
    for (i = 0; i < BOSS_MODE_STEP; i++) {
        if (currentPosition > BOSS_MODE_CODE_LENGTH) {
            currentPosition = 0;
        }
        printf("%c", bossModeCode[currentPosition]);
        currentPosition++;
    }
    return 0;
}

uint8_t isBossKeyPressed() {
    return keyHasBeenPressed(SPACE);
}
