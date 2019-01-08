#include "MKL25Z4.h"
#include "UART.h"

/*
#define bit_mask_2    		0x00000004
#define bit_mask_3    		0x00000008
#define ENABLE_UART0  		0x0C
#define UART0_PIN     		0x00000200
#define UART0_CLK_EN  		0x00000400
#define MCGFKKCLK			0x04000000
#define PORTA_CLK			0x00000200
#define DISABLE_UART0   	0x00
#define BDH_VALUE           0x00
#define BDL_VALUE           0x0C
#define UART0_MODE_SEL      0x00
#define OSR					0x0F
*/

void UART0_init(void);
char uart0_getchar(void);
void uart0_putchar(char ch);

void main_project2()
{
	char uart0_char;
	UART0_init();
	while(1)
	{
		uart0_char = uart0_getchar();
		uart0_putchar(uart0_char);
	}
}

// UART0 initialization
void UART0_init()
{
	SIM_SCGC4 |= UART0_CLK_EN;					// enable clock to UART0
	SIM_SOPT2 |= MCGFKKCLK;						// select MCGFKKCLK as a clock @ 48MHz
	SIM_SCGC5 |= PORTA_CLK;						// enable clock to Port A

	// UART0 configuration for communication
	UART0_C2  = DISABLE_UART0;					// No interrupts, Transmitter and Receiver disabled
	UART0_BDH = BDH_VALUE;						// No interrupts, 1 stop bit
	UART0_BDL = BDL_VALUE;						// Prescaler for 115200 baud rate
	UART0_C1  = UART0_MODE_SEL;					// No loop, UART enabled in wait, 8-bit mode, no parity
	UART0_C4  = OSR;							// Over sampling rate

	// Port configuration to select Alternate 2 pin function
	PORTA_PCR2 |= UART0_PIN;
	PORTA_PCR1 |= UART0_PIN;

	// Enable transmitter and receiver
	UART0_C2  |= ENABLE_UART0;
}

char uart0_getchar(void){
  while(!(UART0_S1 & (1 << 5)));
	return UART0_D;
}

void uart0_putchar(char ch){
  while(!(UART0_S1 & (1 << 7)) && !(UART0_S1 & (1 << 6)));
	UART0_D = ch;
}
