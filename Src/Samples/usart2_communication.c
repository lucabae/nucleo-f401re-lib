/*
	This script makes the Nucleo F401RE talk to the
	computer which it is connected to through USART comms.
*/



#include "usart.h"
#include "gpio.h"
#define MESSAGE "This message will be read on the console\n"
#include <string.h>

int main(void){
	init_gpio_clock('A');
	gpio_set_mode('A', 2, 'F');
	gpio_set_af('A', 2, 7);


	USART_Cfg cfg = {
			.USART_NUM = 2,
			.M = 0,
			.TCIE = 0,
			.TXEIE = 0,
			.RXEIE = 0,
			.BRR = 1666, // For 9600 Baud Rate
			.TE = 1,
			.RE = 0,
			.DMAT = 0,
			.DMAR = 0,

	};
	init_usart(&cfg);

	char message[] = MESSAGE;
	int i = 0;
	int len = strlen(message);

	while(1){
		if(i == len) i = 0;
		set_dr(2, message[i]);
		i++;
		for(volatile int i = 0; i < 300000; i++){}; // Sleep
	}

	return 0;
}
