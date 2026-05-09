#include "adc.h"
#include "gpio.h"

#define MAX_PINS 15


void init_adc_dma_mode(){
	ADC1->CR2 |= (1U << 8) | (1U << 1) | (1U << 9);
}

void init_adc(char port, uint8_t pin){
	if(pin > MAX_PINS){
		while(1){}; // Hard fault
	}

	// set pin in Analog mode
	gpio_set_mode(port, pin, 'A');

	// Activate ADC on RCC clock
  	RCC->APB2ENR |= (1U << 8);


  	// Select pin
    ADC1->SQR3 = pin;
    ADC1->SQR1 = (0 << 20);

  	// ADON Register, set converter ON
  	ADC1->CR2 |= (1U << 0);

	// Wait loop
	for(volatile int i = 0; i < 100000; i++){};

}

void swstart(){
	ADC1->CR2 |= ADC_CR2_SWSTART;
}

uint16_t clean_adc_sampling(){
  uint32_t sum = 0;

  for(int i = 0; i < 16; i++){
    sum += adc_sampling();
  }
  // Divide by 4
  return (uint16_t) (sum >> 4);
}

uint16_t adc_sampling(){
	// Signal start of sampling
	swstart(); // SWSTART Register
	// While SR flag EOC is not 1
	while(((ADC1->SR)&(1U << 1)) == 0){};
	// Return value
	return ADC1->DR;
}
