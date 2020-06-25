/*
**
**                           Main.c
**
**
**********************************************************************/
/*
   Last committed:     $Revision: 00 $
   Last changed by:    $Author: $
   Last changed date:  $Date:  $
   ID:                 $Id:  $

**********************************************************************/
#include "stm32f30x_conf.h"
#include "30010_io.h"
#include "ansi.h"
#include "exercise1.h"
#include "exercise2.h"
#include "exercise3.h"
#include "exercise4.h"
#include "exercise5.h"
#include "exercise6.h"
#include "exercise7.h"
#include "exercise8.h"

int main(void)
{
  uart_init(115200);
  uart_clear();
  clrscr();
  gotoxy(0,0);
  printf("Write a number between 1 and 8 (inclusive) to see the implementation of the corresponding\n");
  printf("coding exercise. Once you have chosen, you will have to manually restart to view another");

  uint8_t exercise = uart_get_char();
  while(!exercise){
    exercise = uart_get_char();
  }

  clrscr();

  switch(exercise){
  case '1':
    exercise1();
    break;
  case '2':
    exercise2();
    break;
  case '3':
    exercise3();
    break;
  case '4':
    exercise4();
    break;
  case '5':
    exercise5();
    break;
  case '6':
    exercise6();
    break;
  case '7':
    exercise7();
    break;
  case '8':
    exercise8();
    break;
  default:
    printf("not valid input");
    break;
  }


  while(1){}
}
