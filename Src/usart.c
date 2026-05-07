#include <usart.h>

USART_TypeDef *get_usart(uint8_t num){
	if(num == 1){
		return USART1;
	} else if(num == 2){
		return USART2;
	} else if(num == 6){
		return USART6;
	}


	return NULL;
}

void init_usart(USART_Cfg* cfg){
	USART_TypeDef* usart = get_usart(cfg->USART_NUM);
	if(usart == NULL) return;

	if(cfg->USART_NUM == 1){
		RCC->APB2ENR |= (1U << 4);
	} else if(cfg->USART_NUM == 6) {
		RCC->APB2ENR |= (1U << 5);
	} else { // 2
		RCC->APB1ENR |= (1U << 17);
	}

	usart->BRR = cfg->BRR;


	usart->CR1 = (cfg->M << 12) |
			(cfg->TXEIE << 7) |
			(cfg->TCIE << 6) |
			(cfg->RXEIE << 5) |
			(cfg->TE << 3) |
			(cfg->RE << 2);

	usart->CR3 = (cfg->DMAT << 7) |
			(cfg->DMAR <<6);


	usart->CR1 |= (1 << 13); // UE
	return;
}


void set_x(uint8_t uart_num, char status, char type){
	// Clean Set or Reset
	if(status != 'S' && status != 'R') return;

	// Get USART Register Pointer
	USART_TypeDef* usart = get_usart(uart_num);
	if(usart == NULL) return;

	// Get if TX or RX
	uint8_t push;
	if(type == 'T') push = 3;
	else if(type == 'R') push = 2;
	else return;

	// Set or Reset
	if(status == 'R'){
		usart -> CR1 &= ~(1U << push);
	} else usart -> CR1 |= (1U << push);
}



uint16_t get_dr(uint8_t uart_num){
	USART_TypeDef* usart = get_usart(uart_num);
	if(usart == NULL) return 0;

	return usart->DR & (0x1FF); // Return with bit mask of 9 bits

}
void set_dr(uint8_t uart_num, uint16_t data){
	USART_TypeDef* usart = get_usart(uart_num);
	if(usart == NULL) return;

	data &= 0x1FFU;

	usart->DR = data;
}


