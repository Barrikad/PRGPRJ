#include "timer.h"

#define FREQUENCY 100 // 100Hz
#define SYSTEM_FREQUENCY 64 * 1000000 // 64MHz

void TIM2_IRQHandler() {
	// Clear update interrupt flag
	TIM2->SR &= ~0x00000001;

	// Increment the duration by one hundredth of a second every time the interrupt runs
	currentDuration.centiseconds++;
	if (currentDuration.centiseconds > 100) {
		currentDuration.centiseconds = 0;
		currentDuration.seconds++;
	}
	if (currentDuration.seconds > 60) {
		currentDuration.seconds = 0;
		currentDuration.minutes++;
	}
	if (currentDuration.minutes > 60) {
		currentDuration.minutes = 0;
		currentDuration.hours++;
	}
}

void initTimer2() {
	// Send power to the timer
	RCC->APB1ENR |= RCC_APB1Periph_TIM2;
	// Configure the timer
	// - No UIFREMAP      (No UIF status bit copying?)
	// - No CKD           (No clock division)
	// - No ARPE          (No ARR buffering)
	// - CMS Edge-aligned (Counter counts up or down depending on DIR)
	// - DIR up           (Counts up)
	// - No OPM           (Counter keeps running (doesn't stop after one event))
	// - Any URS          (Various events can trigger)
	// - UDIS enabled     (Events enabled in general)
	// - No CEN           (Timer disabled, required before setting other values on the timer)
	// Note: reset value for CR1 is 0x0000, so we don't actually need to do anything here - we do it just to make sure.
	TIM2->CR1 = 0x0000;
	// Set reload value
	TIM2->ARR = (const uint32_t) (SYSTEM_FREQUENCY / FREQUENCY - 1);
	// Set prescale value
	TIM2->PSC = 0x0000;
	// Set UIE (Enable update interrupts)
	TIM2->DIER |= 0x00000001;
	// Set interrupt priority, just something high
	NVIC_SetPriority(TIM2_IRQn, 0x1);
	// Enable the timer
	TIM2->CR1 |= 0x01;
}

void enableTimer2() {
	// Enable interrupts for the timer
	NVIC_EnableIRQ(TIM2_IRQn);
}

void disableTimer2() {
	// Disable interrupts for the timer
	NVIC_DisableIRQ(TIM2_IRQn);
}
