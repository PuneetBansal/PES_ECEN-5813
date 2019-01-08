/**********************************************************************************
* FILENAME	    :main.c															  *
* DESCRIPTION	:Contains the main body of the program, to print the new peak     *
* 				 on the terminal.					  							  *
* AUTHOR NAME	:Puneet Bansal & Nachiket Kelkar								  *
* TOOLS USED	:Kinetis Design Studio											  *
***********************************************************************************/

/* ------------------- Includes -------------------- */
#include "board.h"
#include "fsl_lptmr_driver.h"
#include "fsl_debug_console.h"
#include <stdint.h>
#include "adc.h"
#include "dma.h"

/* ------------------- Global variables -------------------- */
int16_t dma_buffer[128];
int buffer_no=0;

/* ----------------------- Defines -------------------------- */
#define first_half 0
#define second_half 64

/* ------------------- Function declaration -------------------- */
void process_info(int);

void main()
{
	hardware_init();
	PRINTF("\n\rWelcome to command line");
	adc_init();
	dma_init();

	/* ---------------- GPIO configuration -------------------- */
	PORTE_PCR22 |= PORT_PCR_MUX(1);
	GPIOE_PDDR  |= 1<<22;

	ADC0_SC1A &= ~(ADC_SC1_ADCH_MASK); 				//adc start
	dma_start();									//dma start

	while(1)
	{
		int buffer_no_now = buffer_no;
		if(buffer_no_now==1)
		{
			process_info(first_half);				//process 1st half of the buffer
		}
		else
		{
			process_info(second_half);				//process 2nd half of the buffer
		}
		while(buffer_no_now==buffer_no);			//wait till buffer is full
	}
}


/* ----------------------- Data processing and displaying results ------------------------ */
void process_info(int region)
{
	int i,peak=0;
	int integer_log_return1;
	float log_return,log_return1;
	static int peak_prev,flag=0;

	peak=(dma_buffer[region]);						//process on ready buffer
	for(i=region;i<region+64;i++)					//process on appropriate buffer
	{
		if(abs(dma_buffer[i])>abs(peak))			//check if new peak is present
		{
			peak=dma_buffer[i];						//update the peak
		}
	}

	// Handle first case
	if(flag==0)
	{
		flag=1;
		peak_prev=peak;
	}
	// if new peak is less than previous assign appropriate decay constant
	else if(abs(peak)<abs(peak_prev) && flag==1)
	{
		float alpha;
		if(abs(peak_prev-peak)<=1000)
		alpha=1;

		else if(abs(peak_prev-peak)<=2000 && abs(peak_prev-peak)>1000)
		alpha=0.97;

		else if(abs(peak_prev-peak)<=4000 && abs(peak_prev-peak)>2000)
		alpha=0.94;

		else if(abs(peak_prev-peak)<=10000 && abs(peak_prev-peak)>4000)
		alpha=0.85;

		else
		alpha=0.7;

		peak = alpha * peak_prev;					//1st order decay of peak
	}
	peak_prev=peak;

	log_return=(float)getlog(abs(peak_prev));		// get the corresponding log value
	log_return1=20*log_return;						// calculate dBFS
	integer_log_return1=log_return1;

	// printing %f logic
	PRINTF("\n\r Peak value in DBFS is : ");
	PRINTF("%d.",integer_log_return1);
	log_return1= ((log_return1-integer_log_return1)*(-1));

	for(int i=0;i<4;i++)
	{
		if(i!=0)
		log_return1-= integer_log_return1;
		log_return1*=10;
		integer_log_return1=log_return1;
		PRINTF("%d",integer_log_return1);
	}
	PRINTF("\n\rThe Peak Value is %d ",peak_prev);
}
