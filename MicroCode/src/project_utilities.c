#include <stdint.h>

int16_t strln(char str[]) {
    int16_t index = 0;
    while(str[index] != '\0') {
        index++;
    }
    return index;
}
