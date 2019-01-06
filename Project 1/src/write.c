
/*
****************************************************************************************************
FILENAME	:write.c
DESCRIPTION	:Function to write the 32-bit contents specified by user at specific memory address
AUTHOR NAME	:Puneet Bansal & Nachiket Kelkar
TOOLS USED	:GCC , GNU MAKE	
****************************************************************************************************
*/


#include<stdio.h>
#include "../inc/allocate.h"
#include "../inc/write.h"
#include <stdlib.h>

int write()
{
   int scan,offset=0;	
   int k=0;
   i=(uint32_t *)malloc(8);					    //initialise 8bytes to i
   uint32_t *address;
   uint32_t value; 
   address=(uint32_t *)malloc(10);

   if(mem==NULL)
   {
      printf("\nNo memory is allocated, allocate memory first\n"); //To check whether memory has been previously allocated or not   
      allocate();
   }

//Prints the list of available addressess on which the user can write the data
   printf("\nThe available addresses on which you can write are\n"); 
   for(i=mem;i<=memlast;i++)
   {
      printf("\n%p",i);	
   }

   printf("\n\nDo you wish to:\
           \n(1)Type the address on which you want to write\
           \n(2)Give an offset from %p\n>>",mem); //Determine whether user wants to input address or offset
   scanf("%d",&scan);
   switch(scan)
   {
      case 1: 
      printf("\nEnter the address on which you want to write the contents\n>>");
      scanf("%p",&address);
      break;
	
      case 2:
      printf("\nEnter the offset from %p\n>>",mem);
      scanf("%d",&offset);
      address=mem+offset;			//Calculate the start address for write
      break;
	
      default:
      printf("Invalid choice");
      break;
   }

   for(i=mem;i<=memlast;i++)			//Loop starts from the starting address of the first block\
						 of allocated memory to the starting add of the last block of allocated memory
   {
      if(i==address)				//If i is equal to the address entered by the user, break from the loop
      {
         printf("\nEnter the 32 bit hex value you want to write\n>>");
	 scanf("%x",i);				//Store the hex value in the address pointed by the pointer i
	 printf("\n**Value Written**");
	 printf("\nEnter the function you would like to perform or type help to see the menu\n>>");
      } 
      else
      {
         k++;					//If i is not equal to address entered by user, increment k
      }
   }


   if(k==size)					//Condition to check whether entered address is valid or not
   {
      printf("\nThe address entered is not a valid address\nType write to try again or help to see other options\n>>");
   }

   return 0;
}
