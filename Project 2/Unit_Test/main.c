/*
***************************************************************************************************************************************
FILENAME	:main.c
DESCRIPTION	:Contains the main body of the program, to run the circular buffer functions and checking the buffer resize capabilty.
AUTHOR NAME	:Puneet Bansal & Nachiket Kelkar
TOOLS USED	:GCC, GNU MAKE	
****************************************************************************************************************************************
*/

/* Include Header Files*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "circular_buffer.h"
#include <time.h>


int main()
{
int i=0;
buffer_status stat;				//Making a variable of type buffer_status to store status of the function called.

cb *tx_buffer,*check;				/*Making pointer objects to the structure cb*/
tx_buffer=malloc(sizeof(cb));			/*Allocating memory to the pointer object*/
tx_buffer->buffer=malloc(sizeof(uint8_t)*10);	/*Allocating memory to the buffer in the structure cb*/
	
check=malloc(sizeof(cb));			/*Allocating memory to the pointer object*/
check->buffer=malloc(sizeof(uint8_t)*10);	/*Allocating memory to the buffer in the structure cb*/	

cb_init(tx_buffer,10);				/*Initialising transmit buffer with size 10*/
//uint8_t *de;

printf("\nAdding 10 elements to the buffer of size 10 and checking status ");
for(i=0;i<10;i++)				/*Loop to add 10 elements in the buffer and print the status and count after each addition */
	{
	stat=cb_add(tx_buffer,i);		/*Storing the status of the function cb_add in variable :status*/
	printf("\nstat is %d,",stat);
	printf("count is %d",tx_buffer->count);
	}

/*The below mentioned code, tries to add a new element to the buffer, but it will fail since the buffer is full now*/
printf("\n\nAdding 11th element to the buffer of size 10");
stat=cb_add(tx_buffer,i);			/*Storing the status of the function in the variable: status*/
printf("\nstat is %d,",stat);
printf("count is %d",tx_buffer->count);

printf("\n\nResizing the buffer to size 15");

/*Function to change the buffer size in runtime. Now the size of the buffer is increased to 15 from 10*/
cb_resize(tx_buffer,15);			

/*Now, we add the 5 more characters to the buffer, and it should accept it*/
printf("\n\nNow Adding 5 more elements to the buffer ");
for(i=10;i<15;i++)
	{
	stat=cb_add(tx_buffer,i);
	printf("stat is %d,",stat);
	printf("count is %d\n",tx_buffer->count);
	}
printf("\n");
return 0;
}
