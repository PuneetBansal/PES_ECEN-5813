/*****************************************************************************
* FILENAME		:UART.c														 *
* DESCRIPTION	:Contains the definitions related to UART config and		 *
* 				 reception and transmission.		 					   	 *
* AUTHOR NAME	:Nachiket Kelkar & Puneet Bansal							 *
* TOOLS USED	:Kinetis Design Studio										 *
******************************************************************************/

/*Including header files */
#include "UART.h"
#include "MKL25Z4.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "circular_buffer.h"

/* Global variable declaration */
char ch1;
uint8_t deleted_element;
extern cb *rx;
extern uint8_t *element_deleted;
extern uint8_t info[256];
extern int tx_flag;
int wait_flag;
buffer_status st;


/* Initializing the UART0 registers for receiving and transmitting characters*/
void UART0_init()
{
	SIM_SCGC4 |= UART0_CLK_EN;				// enable clock to UART0
	SIM_SOPT2 |= MCGFKKCLK;					// select MCGFKKCLK as a clock @ 48MHz
	SIM_SCGC5 |= PORTA_CLK;					// enable clock to Port A

	// UART0 configuration for communication
	UART0_C2  = DISABLE_UART0;				// No interrupts, Transmitter and Receiver disabled
	UART0_BDH = BDH_VALUE;					// No interrupts, 1 stop bit
	UART0_BDL = BDL_VALUE;					// Prescaler for 115200 baud rate
	UART0_C1  = UART0_MODE_SEL;				// No loop, UART enabled in wait, 8-bit mode, no parity
	UART0_C4  = OSR;						// Over sampling rate

	#ifndef Blocking_Uart
	NVIC_EnableIRQ(UART0_IRQn);
    #endif

	// Port configuration to select Alternate 2 pin function
	PORTA_PCR2 |= UART0_PIN;
	PORTA_PCR1 |= UART0_PIN;

  	#ifndef Blocking_Uart
	UART0_C2 = UART0_C2_RIE_MASK;
  	#endif

	// Enable transmitter and receiver
	UART0_C2  |= ENABLE_UART0;

  	#ifndef Blocking_Uart
	__enable_irq();
  	#endif
}

#ifdef Blocking_Uart
/* Blocking function to receive the character over the UART0*/
char uart0_getchar(void)
{
    rx_wait();
	return UART0_D;
}

/* Blocking function to send the character over the UART0*/
void uart0_putchar(char ch)
{
  tx_wait();
  UART0_D = ch;
}
#else

/* Non-Blocking function to receive the character over the UART0*/
char uart0_getchar(void)
{
	return UART0_D;
}

/* Non-Blocking function to send the character over the UART0*/
void uart0_putchar(char ch)
{
	UART0_D = ch;
}
#endif

/* Function to print the string to the screen */
void uart0_putstr(char *str)
{
	while(*str != '\0')
	{
		uart0_putchar(*str);
		for(uint16_t k=0; k<2550; k++);
		str++;
	}
}

/* Function to print the number to the string*/
void putnumber(uint16_t count)
{
	char str[10];
	sprintf(str,"%d",count);
	uart0_putstr(str);
}

/* Blocking function to wait till the transmit flag is set */
void tx_wait()
{
	while(!(UART0_S1 & (1 << 7))); //&& !(UART0_S1 & (1 << 6)));
}

/* Blocking function to wait till the receive flag is set */
void rx_wait()
{
	while(!(UART0_S1 & (1 << 5)));
}

char getch()
{
	return UART0_D;
}

/* Function to put the received character into circular buffer*/
void putch(char ch)
{
	cb_add(rx,ch);
}

/* Interrupt handler for receiving and transmitting the character over the UART0 */
void UART0_IRQHandler(void)
{
	//Receiver interrupt handler
	if(UART0_S1 & UART0_S1_RDRF_MASK)
	{
		ch1=UART0_D;
		putch(ch1);
	}

	//Transmitter interrupt handler
	if(UART0_S1 & UART0_S1_TDRE_MASK)
	{
		tx_flag = 1;
		wait_flag = 1;
		UART0_C2 &= ~(UART0_C2_TIE_MASK);
	}
}

/*Put number inside the buffer*/
void uart0_putstr_nb(char *str)
{
	while(*str != '\0')
	{
		putch(*str);
		str++;
	}
}

/*To get the information of the deleted element of the buffer */
void getinfo(uint8_t *element_deleted)
{
	info[*(element_deleted)]++;
}

