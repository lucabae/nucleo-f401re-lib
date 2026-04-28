#include "gpio.h"
#include "utils.h"

#define MAX_PINS 15

static int clean_gpio_port(char port){
  // Calculate bit_push
  int bit_push = (int) (port - 'A');


  // If port is neither A, B, C, D, or H character.
  if(bit_push < 0 || bit_push > 7 || bit_push == 5 || bit_push == 6){
    return -1;
  }

  return bit_push;
}


void init_gpio_clock(char port){
  int bit_push = clean_gpio_port(port);

  // clean_gpio_port() returns -1 if port is not correct.
  if(bit_push == -1){
    while(1){}; // Hard Fault
  }

  // Activate GPIO port on RCC
  RCC->AHB1ENR |= (1U << bit_push);
}

void gpio_set_mode(char port, uint8_t pin, char mode){
  // If port is not correct
  if(clean_gpio_port(port) == -1){
    while(1){}; // Hard Fault
  }

  // If pin does not exist. This STM32 only counts with 16 pins.
  if(pin > MAX_PINS){
    while(1){}; // Hard Fault
  }

  // Get pointer of the port we are setting the mode in
  GPIO_TypeDef *port_struct = get_port_struct(port);

  // Calculate value to input into register at said pin
  // Mode must be 'I': Input
  //              'O': Output
  //              'F': Alternate Function
  //              'A': Analog
  if(mode != 'I' && mode != 'O' && mode != 'F' && mode != 'A'){
    while(1){}; // Hard Fault
  }

  // Analog:              11
  // Alternate Function:  10
  // Output:              01
  // Input:               00
  uint32_t val = 0U;
  if(mode == 'A'){
    val = 3U;
  } else if(mode == 'O'){
    val = 1U;
  } else if(mode == 'F'){
    val = 2U;
  };


  // Move bits (bit push is multiplied by 2)
  val = (val << (pin << 1));

  // Clean bits
  port_struct->MODER &= ~(3U << (pin << 1));

  // Insert the value into the MODER
  port_struct->MODER |= val;
}



void gpio_write_pin(char port, int pin, char state){
  // State is either 'S' Set or 'R' Reset
  if(state != 'S' && state != 'R'){
    while(1){}; // Hard Fault
  }

  // Clean Port
  if(clean_gpio_port(port) == -1){
    while(1){}; // Hard Fault
  }

  // If pin does not exist.
  if(pin > MAX_PINS){
    while(1){}; // Hard Fault
  }

  // Get pointer of the port we are setting the mode in
  GPIO_TypeDef *port_struct = get_port_struct(port);

  // Set / Reset the pin
  if(state == 'S'){
    port_struct->BSRR = (1U << pin);
  } else if(state == 'R'){
    port_struct->BSRR = (1U << (pin + 16));
  }
}
