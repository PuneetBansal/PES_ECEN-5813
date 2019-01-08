/*****************************************************************************
* FILENAME		:UART.h														 *
* DESCRIPTION	:Contains the declaration related to UART config and		 *
* 				 reception and transmission.		 					   	 *
* AUTHOR NAME	:Nachiket Kelkar & Puneet Bansal							 *
* TOOLS USED	:Kinetis Design Studio										 *
******************************************************************************/

//#ifndef INC_UART_H_
#define INC_UART_H_

/*Including header files */
#include <stdint.h>

/* Defines need for UART configuration */
#define ENABLE_UART0  		0x0C			// Enabling the UART
#define UART0_PIN     		0x00000200		// Configure Pin as UART pins
#define UART0_CLK_EN  		0x00000400		// Enable clock to UART pins
#define MCGFKKCLK			0x04000000		// Selecting the clock source
#define PORTA_CLK			0x00000200		// Enabling clock to Port pins
#define DISABLE_UART0   	0x00			// Disabling the UART
#define BDH_VALUE           0x00			// BDH register value for 115200 baud
#define BDL_VALUE           0x0C			// BDL register value for 115200 baud
#define UART0_MODE_SEL      0x00			// Select UART mode
#define OSR					0x0F			// Over sampling rate

/* Function declaration */
void UART0_IRQHandler(void);
void UART0_init(void);
char uart0_getchar(void);
void uart0_putchar(char);
void uart0_putstr(char *);
void putnumber(uint16_t);
void tx_wait();
void rx_wait();
char getch();
void putch(char);
void uart0_putstr_nb(char *);
void getinfo(uint8_t *);
