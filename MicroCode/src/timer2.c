#include "timer2.h"

static void (*intrpt_ptr)(); //only accessible from file

void initTimer2(uint16_t prescaler, uint16_t reloadValue, void (*fun_ptr)()) {
    intrpt_ptr = fun_ptr;

    RCC->APB1ENR |= RCC_APB1Periph_TIM2;

    TIM2->CR1 = (0 << 11) | (0 << 8) | (0 << 7) | (0 << 5) | (0 << 4) | (0 << 3) | (0 << 2) | (0 << 1) | (0 << 0);

    TIM2->ARR = reloadValue;
    TIM2->PSC = prescaler;
    TIM2->DIER |= 1;
    TIM2->CR1 |= 1;
    NVIC_SetPriority(TIM2_IRQn,1);
    NVIC_EnableIRQ(TIM2_IRQn);
}

void TIM2_IRQHandler(void) {
    (*intrpt_ptr)();
    TIM2->SR &= ~0x0001;
}
