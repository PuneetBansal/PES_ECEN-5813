/*****************************************************************************
* FILENAME		:report.c													 *
* DESCRIPTION	:Contains function definition to print the report to screen	 *
* AUTHOR NAME	:Nachiket Kelkar & Puneet Bansal							 *
* TOOLS USED	:Kinetis Design Studio										 *
******************************************************************************/

/* Including the header files */
#include <report.h>

/* Global variables */
static int wait=1;
extern int wait_flag;
extern int fibo_flag;

/* Function prints the report to the screen using transmitter interrupt and
 * toggles the LED when it is waiting for character to be transmitted.
 */
void generate_report(uint8_t *report_character)
{
	for(uint8_t i=0; i<127; i++)				// Traverse the counter array to check received characters
	{
		if(*(report_character+i) != 0)			// Print only if the character is received
		{
			wait_flag = 1;
			while(wait_flag == 2 || wait_flag == 1)
			{
				if(wait_flag == 1)
				{
					switch(wait)				// To send the next character after interrupt occurs
					{
					case 1:
					{
						uart0_putchar((char)i);
						wait++;
						wait_flag = 2;
						UART0_C2 |= (UART0_C2_TIE_MASK);	// Enable transmitter interrupt
						break;
					}
					case 2:
					{
						uart0_putchar(' ');
						wait++;
						wait_flag = 2;
						UART0_C2 |= (UART0_C2_TIE_MASK);	// Enable transmitter interrupt
						break;
					}
					case 3 :
					{
						uart0_putchar('-');
						wait++;
						wait_flag = 2;
						UART0_C2 |= (UART0_C2_TIE_MASK);	// Enable transmitter interrupt
						break;
					}
					case 4 :
					{
						uart0_putchar(' ');
						wait++;
						wait_flag = 2;
						UART0_C2 |= (UART0_C2_TIE_MASK);	// Enable transmitter interrupt
						break;
					}
					case 5:
					{
						putnumber(*(report_character+i));
						wait++;
						wait_flag = 2;
						UART0_C2 |= (UART0_C2_TIE_MASK);	// Enable transmitter interrupt
						break;
					}
					case 6:
					{
						uart0_putchar('\n');
						wait++;
						wait_flag = 2;
						UART0_C2 |= (UART0_C2_TIE_MASK);	// Enable transmitter interrupt
						break;
					}
					case 7:
					{
						uart0_putchar('\r');
						wait = 9;
						wait_flag = 2;
						UART0_C2 |= (UART0_C2_TIE_MASK);	// Enable transmitter interrupt
						break;
					}
					default:
					{
						wait = 1;
						wait_flag = 0;
					}
					}
				}
			}
		}
		else			// Toggle the LED while waiting for character to be transmitted
		{
			static int change1 = 0;
			if(change1 == 0)
			{
				LED1_TOGGLE;
				change1 = 1;
			}
			else if(change1 == 1)
			{
				LED2_TOGGLE;
				change1 = 2;
			}
			else
			{
				LED3_TOGGLE;
				change1 = 0;
			}
		}
	}
	fibo_flag = 1;		//Flag to print the next fibonacci number
}
