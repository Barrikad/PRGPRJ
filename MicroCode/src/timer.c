#include "timer.h"

static void (*intrpt_ptr2)(); //only accessible from file
static void (*intrpt_ptr3)();
static void (*intrpt_ptr4)();

void initTimer(TIM_TypeDef* tim, uint32_t rcc, uint32_t irq, uint16_t prescaler, uint16_t reloadValue){
    RCC->APB1ENR |= rcc;

    tim->CR1 = (0 << 11) | (0 << 8) | (0 << 7) | (0 << 5) | (0 << 4) | (0 << 3) | (0 << 2) | (0 << 1) | (0 << 0);

    tim->ARR = reloadValue;
    tim->PSC = prescaler;
    tim->DIER |= 1;
    tim->CR1 |= 1;
    NVIC_SetPriority(irq,1);
}

void initTimer2(uint16_t prescaler, uint16_t reloadValue, void (*fun_ptr)()) {
    intrpt_ptr2 = fun_ptr;
    initTimer(TIM2,RCC_APB1Periph_TIM2,TIM2_IRQn,prescaler,reloadValue);
}

void initTimer3(uint16_t prescaler, uint16_t reloadValue, void (*fun_ptr)()) {
    intrpt_ptr3 = fun_ptr;
    initTimer(TIM3,RCC_APB1Periph_TIM3,TIM3_IRQn,prescaler,reloadValue);
}

void initTimer4(uint16_t prescaler, uint16_t reloadValue, void (*fun_ptr)()) {
    intrpt_ptr4 = fun_ptr;
    initTimer(TIM4,RCC_APB1Periph_TIM4,TIM4_IRQn,prescaler,reloadValue);
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
    (*intrpt_ptr2)();
    TIM2->SR &= ~0x0001;
}

void TIM3_IRQHandler(void) {
    (*intrpt_ptr3)();
    TIM3->SR &= ~0x0001;
}

void TIM4_IRQHandler(void) {
    (*intrpt_ptr4)();
    TIM4->SR &= ~0x0001;
}
