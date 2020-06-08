#include <stdint.h>

int16_t strln(char str[]) {
    int16_t index = 0;
    while(str[index] != '\0') {
        index++;
    }
    return index;
}

int32_t expand(int32_t i) {
 // Converts an 18.14 fixed point number to 16.16
 return i << 2;
 }
