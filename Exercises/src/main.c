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
#include "exercise8.h"

int main(void)
{
  uart_init(115200);
  exercise8();
  while(1)
  {

  }
}
