#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h"
#include "stm32f30x.h"
#include "terminal_input.h"

void readCharsInto(uint8_t numberOfChars, char* arr){
    uart_clear();

    int i = 0;
    for(; i < numberOfChars; i++){
        while(uart_get_count() == 0){}
        char c = uart_get_char();

        if(c == 0x0D){break;}

        arr[i] = c;
    }

    arr[i] = 0;
}

