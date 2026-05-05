#include "dma.h"

DMA_Stream_TypeDef *get_dma(uint8_t dma, uint8_t stream){
	if(dma != 1 && dma != 2){
		return NULL;
	}

	if(dma == 1){
		if(stream == 0) return DMA1_Stream0;
		if(stream == 1) return DMA1_Stream1;
		if(stream == 2) return DMA1_Stream2;
		if(stream == 3) return DMA1_Stream3;
		if(stream == 4) return DMA1_Stream4;
		if(stream == 5) return DMA1_Stream5;
		if(stream == 6) return DMA1_Stream6;
		if(stream == 7) return DMA1_Stream7;

		return NULL;
	}
	else {
		if(stream == 0) return DMA2_Stream0;
		if(stream == 1) return DMA2_Stream1;
		if(stream == 2) return DMA2_Stream2;
		if(stream == 3) return DMA2_Stream3;
		if(stream == 4) return DMA2_Stream4;
		if(stream == 5) return DMA2_Stream5;
		if(stream == 6) return DMA2_Stream6;
		if(stream == 7) return DMA2_Stream7;

		return NULL;
	}
}

void init_dma(DMA_Config *cnf){
	DMA_Stream_TypeDef *dma = get_dma(cnf->dma, cnf->stream);
	if(dma == NULL) return;
	if((dma->CR & (1 << 0)) == 1) return; // Can't do changes while enabled


	dma->CR = 	(cnf->channel << 25) |
				(cnf->msize << 13) 	|
				(cnf->psize << 11)	|
				(cnf->minc << 10)	|
				(cnf->pinc << 9)	|
				(cnf->circ << 8)	|
				(cnf->direction<<6)	|
				(cnf->tcie << 4)	|
				(cnf->htie << 3)	|
				(cnf->teie << 2)	;



	dma->NDTR = cnf->ndtr;
	dma->PAR = cnf->par;
	dma->M0AR = cnf->m0ar;
	dma->M1AR = cnf->m1ar;
	dma->FCR = 	(cnf->dmdis << 2) 	|
				(cnf->fth << 0)		;




}

void dma_en(uint8_t dma, uint8_t stream_num, uint8_t status){
	if(status != 0 && status != 1){
		return;
	}


	DMA_Stream_TypeDef *stream = get_dma(dma, stream_num);
	if(stream == NULL) return;



	if(status == 0){
		stream->CR &= ~(1 << 0);
	}
	else {
		stream->CR |= (1 << 0);
	}
}
