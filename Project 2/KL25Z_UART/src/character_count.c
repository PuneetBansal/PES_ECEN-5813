/*****************************************************************************
* FILENAME		:character_count.c											 *
* DESCRIPTION	:Contains function to get the character and increment the    *
*                no of those characters received	 					   	 *
* AUTHOR NAME	:Nachiket Kelkar & Puneet Bansal							 *
* TOOLS USED	:Kinetis Design Studio										 *
******************************************************************************/

/* Including header files */
#include "character_count.h"

/* Global declarations */
uint8_t cc[256];


/* Function receives the character and updates the number of those characters
 * received from the UART into the array. */
uint8_t* character_count(uint8_t *report_char)
{
	cc[*report_char] ++;			//increase the count of received character
	return cc;
}


