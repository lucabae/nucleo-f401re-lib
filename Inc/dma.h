/*
 * dma.h
 *
 *  Created on: 28 abr 2026
 *      Author: luca
 */

#ifndef DMA_H_
#define DMA_H_

#include <stm32f4xx.h>
#include <stdint.h>
#define NULL ((void*)0) // define NULL



typedef struct {
    // Selection
    uint8_t dma;        // 1 or 2
    uint8_t stream;     // 0-7
    uint8_t channel;    // 0-7

    // Transfer
    uint8_t direction; 	// 00: P to M
    					// 01: M to P
    					// 10: M to M
    					// 11: reserved
    					// These must be in binary not decimal
    uint8_t msize;	// 00: byte
    				// 01: 2 bytes
    				// 10 : 4 bytes
    uint8_t psize;// Same as MSIZE
    uint8_t minc; // 0 fixed 1 increment
    uint8_t pinc; // 0 fixed 1 increment
    uint8_t circ; // 0 disabled 1 enabled

    // Interrupts
    uint8_t tcie; // Transfer complete
    uint8_t htie; // Half transfer
    uint8_t teie; // Transfer error

    // Pointers
    uint32_t par;
    uint32_t m0ar;
    uint32_t m1ar;
    uint16_t ndtr;

    // FIFO
    uint8_t dmdis;
    uint8_t fth; 	// FIFO threshold selection
    				// 00: 1/4
    				// 01: 1/2
    				// 10: 3/4
    				// 11: full

} DMA_Config;

void init_dma(DMA_Config *cnf);
void dma_en(uint8_t dma, uint8_t stream_num, uint8_t status);


#endif /* DMA_H_ */
