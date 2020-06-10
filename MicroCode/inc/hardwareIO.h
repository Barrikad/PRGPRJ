#ifndef HARDWAREIO_H_INCLUDED
#define HARDWAREIO_H_INCLUDED
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h"
#include "stm32f30x.h"

void initInput(int8_t pin, char port);
void initOutput(int8_t pin, char port);

uint8_t getInput(int8_t pin, char port);
void setOutput(int8_t pin, char port, uint8_t on);

void initJoystick();
void initLeds();

void setLeds(uint8_t color);
uint8_t readJoystick();

void initLeds();

void setLeds(uint8_t color);

void ledToJoystick();

#endif /* HARDWAREIO_H_INCLUDED */
