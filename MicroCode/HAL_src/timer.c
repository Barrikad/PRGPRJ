#include "timer.h"

// 64MHz.
#define CPU_FREQUENCY 64000000

// Functions that will be called when the timers trigger.
static volatile void (*timer2_interrupt_ptr)();
static volatile void (*timer3_interrupt_ptr)();
static volatile void (*timer4_interrupt_ptr)();

static void _initTimer(TIM_TypeDef* tim, uint32_t rcc, uint32_t irq, uint16_t prescaleValue, uint32_t reloadValue) {
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
    tim->PSC = prescaleValue;
    // Set UIE (Enable update interrupts)
    tim->DIER |= 0x00000001;
    // Enable the timer
    TIM2->CR1 |= 0x0001;
    // Set interrupt priority, just something high
    NVIC_SetPriority(irq, 1);
}

static void _initTimerWithFrequency(TIM_TypeDef* tim, uint32_t rcc, uint32_t irq, uint16_t frequency) {
    uint16_t prescaleValue = 0;
    uint32_t reloadValue = (uint32_t) frequency * CPU_FREQUENCY / ((uint32_t) prescaleValue + 1) - 1;
    _initTimer(tim, rcc, irq, prescaleValue, reloadValue);
}

void initTimer2WithFrequency(void (*function_ptr)(), uint16_t frequency) {
    timer2_interrupt_ptr = function_ptr;
    _initTimerWithFrequency(TIM2, RCC_APB1Periph_TIM2, TIM2_IRQn, frequency);
}

void initTimer3WithFrequency(void (*function_ptr)(), uint16_t frequency) {
    timer3_interrupt_ptr = function_ptr;
    _initTimerWithFrequency(TIM3, RCC_APB1Periph_TIM3, TIM3_IRQn, frequency);
}

void initTimer4WithFrequency(void (*function_ptr)(), uint16_t frequency) {
    timer4_interrupt_ptr = function_ptr;
    _initTimerWithFrequency(TIM4, RCC_APB1Periph_TIM4, TIM4_IRQn, frequency);
}

void enableTimer2() {
    NVIC_EnableIRQ(TIM2_IRQn);
}

void disableTimer2() {
    NVIC_DisableIRQ(TIM2_IRQn);
}

void enableTimer3() {
    NVIC_EnableIRQ(TIM3_IRQn);
}

void disableTimer3() {
    NVIC_DisableIRQ(TIM3_IRQn);
}

void enableTimer4() {
    NVIC_EnableIRQ(TIM4_IRQn);
}

void disableTimer4() {
    NVIC_DisableIRQ(TIM4_IRQn);
}

void TIM2_IRQHandler(void) {
    // Call registered function
    (*timer2_interrupt_ptr)();
    // Clear update interrupt flag
    TIM2->SR &= ~0x0001;
}

void TIM3_IRQHandler(void) {
    // Call registered function
    (*timer3_interrupt_ptr)();
    // Clear update interrupt flag
    TIM3->SR &= ~0x0001;
}

void TIM4_IRQHandler(void) {
    // Call registered function
    (*timer4_interrupt_ptr)();
    // Clear update interrupt flag
    TIM4->SR &= ~0x0001;
}
