/*

This sample code gets the value of a potentio-meter connected
to the A0 pin, and blinks the LED at a speed according to it using DMA.

*/


#include "dma.h"
#include "gpio.h"
#include "adc.h"
#include <stdio.h>

volatile uint16_t buffer[16];
volatile int iterations = 500000; // Amount of iterations used in the waiting loop of the main function

void DMA2_Stream0_IRQHandler(){
	DMA2->LIFCR |= DMA_LIFCR_CTCIF0;
	uint32_t avg = 0;
	for(int i = 0; i < 16; i++) avg += buffer[i];

	// 65 000 + (avg / 16) * 128
	iterations = (1U << 16) + (avg << 3);
};



int main(){
	init_gpio_clock('A');
	gpio_set_mode('A', 5, 'O');
	init_adc('A', 0);
	init_adc_dma_mode();

	DMA_Config cfg = {
			.dma = 2,
			.channel = 0,
			.stream = 0,

			.direction = 0,

			.msize = 1,
			.psize = 1,

			.pinc = 0,
			.minc = 1,
			.circ = 1,

			.tcie = 1,
			.htie = 0,
			.teie = 0,

			.par = (uint32_t) &ADC1->DR,
			.m0ar = (uint32_t) buffer,
			.m1ar = 0,
			.ndtr = 16,

			.dmdis = 0,
			.fth = 0,
	};

	init_dma(&cfg);
	NVIC_EnableIRQ(DMA2_Stream0_IRQn);

	dma_en(2, 0, 1);
	swstart();

	// Wait that does not do any calculations
	while(1){
		gpio_write_pin('A', 5, 'S');
		for(volatile int i = 0; i < iterations; i++){}
		gpio_write_pin('A', 5, 'R');
		for(volatile int i = 0; i < iterations; i++){}

	};


	return 0;
}
