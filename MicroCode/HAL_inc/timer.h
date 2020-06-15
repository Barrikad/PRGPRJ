#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

// Note: The functions in here are not generic like they are in e.g. led.h or
// joystick.h, since the interrupt pointer can't (easily) be!

#include <stdint.h>
#include "stm32f30x_conf.h"

// Initialize the second timer.
// The given function will be called with an interval of "frequency" Hz.
// This MUST only called while the timer is disabled!
void initTimer2WithFrequency(void (*function_ptr)(), uint16_t frequency);

// Initialize the third timer.
// The given function will be called with an interval of "frequency" Hz.
// This MUST only called while the timer is disabled!
void initTimer3WithFrequency(void (*function_ptr)(), uint16_t frequency);

// Initialize the fourth timer.
// The given function will be called with an interval of "frequency" Hz.
// This MUST only called while the timer is disabled!
void initTimer4WithFrequency(void (*function_ptr)(), uint16_t frequency);

// Enable interrupts for the second timer. By default, the timer is disabled.
void enableTimer2();

// Disable interrupts for the second timer.
void disableTimer2();

// Enable interrupts for the third timer. By default, the timer is disabled.
void enableTimer3();

// Disable interrupts for the third timer.
void disableTimer3();

// Enable interrupts for the fourth timer. By default, the timer is disabled.
void enableTimer4();

// Disable interrupts for the fourth timer.
void disableTimer4();

#endif /* TIMER2_H_INCLUDED */
