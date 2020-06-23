#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h"
#include "stm32f30x.h"

//The array registers which keys have been pressed. Each bit is on if a corresponding character has been pressed.
//The first bit represent 32 in ascii (space), and the last represents 32+95 in ascii. The range is from 32 to 127
static uint32_t keylog[3];

void clearKeys(){
    keylog[0] = 0;
    keylog[1] = 0;
    keylog[2] = 0;
    uart_clear();
}

uint16_t keyHasBeenPressed(char key){
    key = key - 32;

    uint8_t keyPress = uart_get_char();
    while(keyPress) {
        keyPress = keyPress - 32;
        keylog[keyPress/3] |= (1 << (keyPress - 32*(keyPress/3)));
        keyPress = uart_get_char();
    }

    return keylog[key/3] & (1 << (key - 32*(key/3)));
}
