/**********************************************************************************
* FILENAME	    :dma.c															  *
* DESCRIPTION	:dma initialization and reading values using dma				  *
* AUTHOR NAME	:Nachiket Kelkar & Puneet Bansal								  *
* TOOLS USED	:Kinetis Design Studio											  *
***********************************************************************************/

#include "dma.h"

extern int16_t dma_buffer[128];
extern int buffer_no;
uint32_t dma_address, dma_address1;

uint32_t a=10;

void dma_init()
{
	SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;					// Clock to DMA mux
	SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;					// Clock to DMA module

	DMAMUX0_CHCFG0 = 0x00;								// Disable DMA

	DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;				// Clearing previous errors
	DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;				// Ensuring the clear
	DMA_SAR0 = 0x4003B010;								// Source Address
	DMA_DSR_BCR0 |=DMA_DSR_BCR_BCR(128);				// No of bytes to be transferred = (4 * 64)= 256 bytes
	DMA_DCR0 &= ~(DMA_DCR_SSIZE_MASK | DMA_DCR_DSIZE_MASK); //clear source size and destination size fields

	// Select DMA source size, destination size, enable interrupts, enable peripheral request,
	// wait till conversion is complete, destination increment, source and destination buffer disable
	DMA_DCR0 |= (DMA_DCR_SSIZE(2) | DMA_DCR_DSIZE(2) | DMA_DCR_D_REQ_MASK  | DMA_DCR_DINC_MASK);
	DMA_DCR0 |= (DMA_DCR_CS_MASK  | DMA_DCR_ERQ_MASK  | DMA_DCR_EADREQ_MASK  | DMA_DCR_EINT_MASK);

	dma_address= (uint32_t)&dma_buffer;
	dma_address1= (uint32_t)&dma_buffer[64];
	DMA_DAR0 = dma_address;								// Destination address

	DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_SOURCE(40);			// Select source as ADC0
	DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_ENBL_MASK;			// Enable DMA MUX

	__enable_irq();										// Enable interrupts
	NVIC_EnableIRQ(DMA0_IRQn);							// Enable NVIC DMA0 interrupt
}

void dma_start()
{
	DMA_DCR0 |= DMA_DCR_ERQ_MASK ;			// Start the DMA transfer, Enable dma through peripheral
}

float getlog(float input)
{
	float check1=1;
	int i=0;
	for(i=0;i<20;i++)
	{
		if(input<=lookup[i].max_val && input>=lookup[i].min_val)
		{
			check1=lookup[i].log_output;
		}
	}
return check1;
}


void DMA0_IRQHandler(void)
{
	GPIOE_PSOR |= (1<<22);										//Set GPIO pin
/* ---------------- Check for any errors -------------------- */
	if(DMA_DSR_BCR0 & DMA_DSR_BCR_CE_MASK)
	{
		PRINTF("\n\rinterrupt due to configuration error");
	}
	if(DMA_DSR_BCR0 & DMA_DSR_BCR_BES_MASK)
	{
		PRINTF("\n\rinterrupt due to bus error on source");
	}
	if(DMA_DSR_BCR0 & DMA_DSR_BCR_BED_MASK)
	{
		PRINTF("\n\rinterrupt due to bus error in destination");
	}

	DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;				    // Clearing previous errors
	DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;				    // Clearing previous errors

	GPIOE_PCOR |= (1<<22);									// Clear GPIO pin

	// provide appropriate buffer to fill the ADC values to DMA
	if(buffer_no==1)
	{
	DMA_DAR0 = dma_address;
	buffer_no=0;
	}
	else
	{
	DMA_DAR0= dma_address1;
	buffer_no=1;
	}
	DMA_DSR_BCR0 |=DMA_DSR_BCR_BCR(128);					// No of bytes of data to transfer
	dma_start();											// Start dma operations
}

