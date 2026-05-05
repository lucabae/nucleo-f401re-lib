#ifndef GPIO_H
#define GPIO_H

#include <stm32f4xx.h>
#include <stdint.h>


void init_gpio_clock(char port);
void gpio_set_mode(char port, uint8_t pin, char mode);
void gpio_write_pin(char port, int pin, char state);
#define NULL ((void*)0) // define NULL

#endif // GPIO_H
