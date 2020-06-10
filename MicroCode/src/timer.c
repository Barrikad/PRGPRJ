#include "timer.h"

static void (*intrpt_ptr2)(); //only accessible from file
static void (*intrpt_ptr3)();
static void (*intrpt_ptr4)();

void initTimer(TIM_TypeDef* tim, uint32_t rcc, uint32_t irq, uint16_t prescaler, uint16_t reloadValue) {
	// Send power to the timer
    RCC->APB1ENR |= rcc;

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
    tim->CR1 = (0 << 11) | (0 << 8) | (0 << 7) | (0 << 5) | (0 << 4) | (0 << 3) | (0 << 2) | (0 << 1) | (0 << 0);
	// Set reload value
    tim->ARR = reloadValue;
	// Set prescale value
    tim->PSC = prescaler;
	// Set UIE (Enable update interrupts)
    tim->DIER |= 0x00000001;
	// Enable the timer
	TIM2->CR1 |= 0x0001;
	// Set interrupt priority, just something high
    NVIC_SetPriority(irq, 1);
}

void initTimer2(uint16_t prescaler, uint16_t reloadValue, void (*fun_ptr)()) {
    intrpt_ptr2 = fun_ptr;
    initTimer(TIM2, RCC_APB1Periph_TIM2, TIM2_IRQn, prescaler, reloadValue);
}

void initTimer3(uint16_t prescaler, uint16_t reloadValue, void (*fun_ptr)()) {
    intrpt_ptr3 = fun_ptr;
    initTimer(TIM3, RCC_APB1Periph_TIM3, TIM3_IRQn, prescaler, reloadValue);
}

void initTimer4(uint16_t prescaler, uint16_t reloadValue, void (*fun_ptr)()) {
    intrpt_ptr4 = fun_ptr;
    initTimer(TIM4, RCC_APB1Periph_TIM4, TIM4_IRQn, prescaler, reloadValue);
}

void enableTimer2() {
	// Enable interrupts for the timer
	NVIC_EnableIRQ(TIM2_IRQn);
}

void enableTimer3() {
	// Enable interrupts for the timer
	NVIC_EnableIRQ(TIM3_IRQn);
}


void enableTimer4() {
	// Enable interrupts for the timer
	NVIC_EnableIRQ(TIM4_IRQn);
}

void disableTimer2() {
	// Disable interrupts for the timer
	NVIC_DisableIRQ(TIM2_IRQn);
}

void disableTimer3() {
	// Disable interrupts for the timer
	NVIC_DisableIRQ(TIM3_IRQn);
}

void disableTimer4() {
	// Disable interrupts for the timer
	NVIC_DisableIRQ(TIM4_IRQn);
}

void TIM2_IRQHandler(void) {
	// Call registered function
    (*intrpt_ptr2)();
	// Clear update interrupt flag
    TIM2->SR &= ~0x0001;
}

void TIM3_IRQHandler(void) {
	// Call registered function
    (*intrpt_ptr3)();
	// Clear update interrupt flag
    TIM3->SR &= ~0x0001;
}

void TIM4_IRQHandler(void) {
	// Call registered function
    (*intrpt_ptr4)();
	// Clear update interrupt flag
    TIM4->SR &= ~0x0001;
}
