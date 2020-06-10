#include <stdint.h>

#ifndef HARDWAREIO_H_INCLUDED
#define HARDWAREIO_H_INCLUDED

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
