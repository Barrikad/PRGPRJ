#include "display.h"

static uint8_t buffer[512];
static uint8_t flag;

void initDisplay(){
    memset(buffer,0,512);
    lcd_push_buffer(buffer);
}

void lcdWriteString(char str[], uint8_t line, uint8_t slice){
    uint8_t index = 0;
    while(!(str[index] == 0)){
        for(int i = 0; i < 5; i++){
            buffer[line*128 + slice + index*5 + i] = character_data[str[index] - 0x20][i];
        }
        index++;
    }
    lcd_push_buffer(buffer);
}

void setFlag(){
    flag = 1;
}

void lcdUpdate(){
    if(flag){
        for(int i = 0; i < 4; i++){
            char first = buffer[i*128];
            for(int j = 0; j < 127; j++){
                buffer[i*128 + j] = buffer[i*128 + j + 1];
            }
            buffer[i*128 + 127] = first;
        }
        lcd_push_buffer(buffer);
    }
    flag = 0;
}
