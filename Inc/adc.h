/*
 * adc.h
 *
 *  Created on: 28 abr 2026
 *      Author: luca
 */

#ifndef ADC_H_
#define ADC_H_



#endif /* ADC_H_ */
#ifndef ADC_H
#define ADC_H

#include <stdint.h>
#include <stm32f4xx.h>

void init_adc(char port, uint8_t pin);
void init_adc_dma_mode(); // To be ran before init_adc function
void swstart(); // Initiates a conversion
uint16_t clean_adc_sampling();
uint16_t adc_sampling();

#endif
