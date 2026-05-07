/*
 * uart.h
 *
 *  Created on: 7 may 2026
 *      Author: luca
 */

#ifndef USART_H_
#define USART_H_

#include <stdint.h>
#include <stm32f4xx.h>



typedef struct {
	uint8_t USART_NUM; // USART1, USART2 or USART6
	uint8_t M; 		// Word Size: 0=8 bits, 1=9 bits
	uint8_t TXEIE; 	// TXE Interrupt Enable
	uint8_t TCIE; 	// TC Interrupt Enable
	uint8_t RXEIE;	// RXE Interrupt Enable
	uint16_t BRR; 	// Baud Rate: f_CK / Baud Rate
	uint8_t TE; 	// TX Enable
	uint8_t RE; 	// RX Enable
	uint8_t DMAT; 	// TX DMA
	uint8_t DMAR;	// RX DMA
} USART_Cfg;



void init_usart(USART_Cfg* cfg);
void set_x(uint8_t uart_num, char status, char type); 	// Status: 'S' or 'R'
														// Type: 'T' or 'R'
uint16_t get_dr(uint8_t uart_num); // Returns 16 bits with bit 15 to 9 cleared
void set_dr(uint8_t uart_num, uint16_t data); // Bits 15 to 9 are cleared

#define NULL ((void*)0)

#endif /* UART_H_ */
