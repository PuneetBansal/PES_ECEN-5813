/**********************************************************************************
* FILENAME	    :main.c															  *
* DESCRIPTION	:Contains the main body of the program, to print the report when  *
* 				 any character is received			  							  *
* AUTHOR NAME	:Puneet Bansal & Nachiket Kelkar								  *
* TOOLS USED	:Kinetis Design Studio											  *
***********************************************************************************/

/* Include Header Files*/
#include <stdint.h>
#include <stdlib.h>
#include "board.h"
#include "fsl_lptmr_driver.h"
#include "fsl_debug_console.h"
#include "MKL25Z4.h"
#include "UART.h"
#include "circular_buffer.h"
#include "character_count.h"
#include "report.h"

/* Global variables*/
cb *rx;
uint8_t *element_deleted;
uint8_t* info;
int tx_flag=1;
int count=0;
int fibo_flag;
cb rx_buf;
char recv;

/* Main function initializes the LED, UART and circular buffer
 * It deletes the character in the buffer and updates the counter
 * array and displays the updated report. When no character are
 * being received it calculates next fibonacci number and prints
 * it to the screen and also toggles the LED in the free time.
 */
int main (void)
{
	LED1_EN;
	LED2_EN;
	LED3_EN;
	rx= malloc(sizeof(cb));				// Allocate space for the buffer
	rx->buffer=malloc(1000);			// Allocate space for the buffer
	cb_init(rx,1000);					// Initialize the circular buffer
	element_deleted= malloc(2);

	UART0_init();						// Initialize the UART

    buffer_status  status;
	while(1)
	{
		if(tx_flag==1)
		{
			//tx_flag=0;
			status = cb_delete(rx,element_deleted);
			if (status != cb_empty)								// Check if the buffer is not empty
			{
				info = character_count(element_deleted);		// Updating the counter array
				generate_report(info);							// Print the report to the screen
				UART0_C2 |= (UART0_C2_TIE_MASK);
			}
			else												// Calculate the fibonacci number in free time
			{
				if(fibo_flag == 1)
				{
					uart0_putstr("fibo = ");
					static uint16_t fibo=1, fibo1=0, temp;
					temp = fibo;
					fibo = fibo + fibo1;
					fibo1 = temp;
					putnumber(fibo);
					uart0_putstr("\n\r");
					uart0_putstr("\n\r");
					fibo_flag = 0;
					if(fibo >= 46368)				// reloading the values when count exceed the integer limit
					{
						fibo = 1;
						fibo1 = 0;
					}
				}
				static int change = 0;
				if(change == 0)						// Toggle LED when characters are not received
				{
					LED1_TOGGLE;
					change = 1;
					for(uint16_t i=0; i<65530; i++);
				}
				else if(change == 1)				// Toggle LED when characters are not received
				{
					LED2_TOGGLE;
					change = 2;
					for(uint16_t i=0; i<65530; i++);
				}
				else								// Toggle LED when characters are not received
				{
					LED3_TOGGLE;
					change = 0;
					for(uint16_t i=0; i<65530; i++);
				}
			}
		}
	}
}
