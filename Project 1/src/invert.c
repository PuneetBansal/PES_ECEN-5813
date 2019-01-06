
/*
********************************************************************************************************************************
FILENAME	:invert.c
DESCRIPTION	:Function to invert all memory bits in specified area of memory
AUTHOR NAME	:Puneet Bansal & Nachiket Kelkar
TOOLS USED	:GCC, GNU MAKE	
REFERENCES	:The logic for clock refered from https://www.geeksforgeeks.org/how-to-measure-time-taken-by-a-program-in-c/	
*********************************************************************************************************************************
*/


#include <stdio.h>
#include "../inc/invert.h"
#include "../inc/allocate.h"
#include "../inc/write.h"
#include <time.h>

int invert()
{
   clock_t first= clock();		        //Store the value of clock() in the variable first
   int scan, offset=0;
   uint32_t number=0xffffffff;
   int k=1;int l;
   if(mem==NULL)          			//To check whether memory has been allocated or not
   {
      printf("There is no memory allocated");		   
   }
   else
   {
      printf("\n\nDo you wish to:\
              \n(1)Type the address whose data you want to see\
              \n(2)Give an offset from %p\n>>",mem);
      scanf("%d",&scan);
      switch(scan)				//Check whether the user wants to input address or offset
      {
         case 1: 
	 printf("\nEnter the address on which you want to see the contents\n>>");
	 scanf("%p",&u_inv_add);		//Get the memory address from the user
	 break;
	 
	 case 2:
	 printf("\nEnter the offset from %p\n>>",mem);
	 scanf("%d",&offset);
	 u_inv_add=mem+offset;			//Calculate the start address of the user needed memory
	 break;
	
	 default:
	 printf("Invalid choice");
	 break;
      }
	
   printf("\nEnter the no of blocks you want to invert\t\n>>");
   scanf("%d",&noofblocks);
   count=(uint32_t *)malloc(8);

   for(count=mem;count<=memlast;count++)	//Loop from the starting address to starting add of last block of allocated memory
   {
      if(count==u_inv_add)			//If count is equal to the address entered by the user, break from the loop
      {
         break;		
      }
      else
      {
         k++;					//If count is not equal to address entered by user, increment k
      }
   }
   if(k==(size+1))				//Condition to check whether entered address is valid or not	
   {
      printf("\nMemeory entered is not valid\nType disp to try again or help to see the menu\n>>");
   }
   else if(noofblocks<=(size-(k-1)))		//Condition to check whether the entered block size is valid or not
   {
      for(l=0;l<noofblocks;l++)
      {
          
	 *count=*count^number;
	 printf("\nThe complemented value at address %p is %x\n",count,*count); 
	 count++;
      }
   printf("\nType the function you would like to perform or type help to see the menu\n>>");	
   }
   else
   {
   printf("The number of blocks entered is invalid\
	  \nType disp to try again or help to see the menu\n>>");}
   }
   clock_t second=clock();		//Store the value of clock() in the variable second
   printf("\nTime taken to perform the entire invert function is=%f seconds",(double)(second-first)/CLOCKS_PER_SEC);
   return 0;
}
