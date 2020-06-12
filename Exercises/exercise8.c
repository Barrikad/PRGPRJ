#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h"
#include "stm32f30x.h"
#include "hardware_io.h"

static const uint8_t channels[] = {0,ADC_Channel_1,ADC_Channel_2,ADC_Channel_3,ADC_Channel_4,
                                     ADC_Channel_5,ADC_Channel_6,ADC_Channel_7,ADC_Channel_8,
                                     ADC_Channel_9,ADC_Channel_10,ADC_Channel_11,ADC_Channel_12,
                                     ADC_Channel_13,ADC_Channel_14,ADC_Channel_15};

void initADC(){
    //CONFIGURE
    RCC->CFGR2 &= ~RCC_CFGR2_ADCPRE12;     //clear prescaler
    RCC->CFGR2 |= RCC_CFGR2_ADCPRE12_DIV6; //set prescaler to 12
    RCC->AHBENR |= RCC_AHBPeriph_ADC12;    //enable clock

    ADC1->CR = 0; //clear register
    ADC1->CFGR &= 0xFDFFC007; //clear config register
    ADC1->SQR1 &= ~ADC_SQR1_L; //clear regular sequence register. Dunno why

    //CALIBRATE
    ADC1->CR |= 0x10000000; //enable voltage regulator
    for(int i = 0; i < 1000; i++){} //wait 1000 cycles

    ADC1->CR |= 0x80000000; //start calibration
    while(ADC1->CR & 0x80000000){} //wait for calibration to finish
    for(int i = 0; i < 100; i++){} //wait 100 cycles

    //ENABLE
    ADC1->CR |= 1; //enable adc
    while(!(ADC1->ISR & 1)){} //wait until ready

}

uint16_t readADC(uint8_t channel){
    ADC_RegularChannelConfig(ADC1,channels[channel],1,ADC_SampleTime_1Cycles5); //configure to read from the given channel
    ADC_StartConversion(ADC1); //start read
    while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == 0); //wait for read
    return ADC_GetConversionValue(ADC1); //return read
}

void exercise8() {
    initADC();
    uint16_t x = readADC(1);
    uint16_t y = readADC(2);
    printf("\n%04i;%04i",x,y);
}
