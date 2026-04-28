#include "utils.h"
#include <stddef.h>

GPIO_TypeDef *get_port_struct(char port){
  switch(port){
    case 'A':
      return GPIOA;
    case 'B':
      return GPIOB;
    case 'C':
      return GPIOC;
    case 'D':
      return GPIOD;
    case 'H':
      return GPIOH;
    default:
      return NULL;
  }
}
