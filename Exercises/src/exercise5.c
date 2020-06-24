#include "hardware_io.h"
void exercise5(){
    initLeds();
    initJoystick();

    gotoxy(1,1);
    printf("Use joystick to control led");
    while(1){
        ledToJoystick();
    }
}
