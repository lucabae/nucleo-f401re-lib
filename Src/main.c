#include "gpio.h"
#include "adc.h"
#include <stdint.h>

int main(void){

	init_gpio_clock('A');

	gpio_set_mode('A', 5, 'O');

	gpio_set_mode('A', 0, 'A');
	init_adc('A', 0);



	while(1){
		uint16_t potentio = clean_adc_sampling();
		// Minimum of 250 000 iterations: 2^18 ~= 250 000
		// Multiplying the potentio by 500 ~= 2^9
		int delay = (potentio << 9) + (1U << 18);

		gpio_write_pin('A', 5, 'S');
		for(volatile int i = 0; i < delay; i++){};
		gpio_write_pin('A', 5, 'R');
		for(volatile int i = 0; i < delay; i++){};
	}


	return 0;
}
