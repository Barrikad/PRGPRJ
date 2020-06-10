#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "ansi.h"
#include "arithmatic.h"
#include "project_utilities.h"
#include "hardwareIO.h"
#include "exercise6.h"

void createEnemy(){}

int main(void)
{
    uart_init(115200);
    initTimer3(4000,12342,createEnemy);
    clrscr();
    exercise6();
}
