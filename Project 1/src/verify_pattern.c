
/*
***************************************************************************************************************************
FILENAME	:verify_pattern.c
DESCRIPTION	:Function to verify the pattern to the contents of memory in unsigned 32-bit hexadecimal format.
                 The user may specify an address, seed value and the number of 32bit words to verify.
AUTHOR NAME	:Nachiket Kelkar & Puneet Bansal
TOOLS USED	:GCC, GNU MAKE			
***************************************************************************************************************************
*/

#include <stdio.h>
#include <stdint.h>
#include "../inc/write.h"
#include "../inc/Pattern_gen.h"
#include "../inc/verify_pattern.h"
#include "../inc/allocate.h"
#include "../inc/disp.h"
#include <time.h>

int verify_pattern()
{
   long pattern;
   int scan,offset=0,length,seed_value,k=1,l,wa_len=0,inc=0,inc1=0;
   uint32_t *address;
   uint64_t wrong[size];
   clock_t first,second;
   
   address=(uint32_t *)malloc(8);
   if(mem==NULL)			//To check whether memory has been allocated or not
   {
      printf("No memory is allocated, allocate memory first and run function again\n>>");
      printf("allocate\n");
      allocate();
   }
   else
   {
      printf("The available addresses on which you can verify are\n");
      for(i=mem;i<=memlast;i++)		//Loop starts from starting address of the first block of allocated \
					  memory to the starting add of the last block of allocated memory
      {
	 printf("\n%p",i);
      }
      printf("\n\nDo you wish to:\
              \n(1)Type the address whose data you want to see\
              \n(2)Give an offset from %p\n>>",mem);
      scanf("%d",&scan);
      switch(scan)			//Check whether the user wants to input address or offset
      {
         case 1: 
	 printf("\nEnter the address on which you want to see the contents\n>>");
	 scanf("%p",&address);		//Get the memory address from the user
	 break;
	
	 case 2:
	 printf("\nEnter the offset from %p\n>>",mem);
	 scanf("%d",&offset);
	 address=mem+offset;		//Calculating the starting address of the memory that user wants \
                                          to display using offset
	 break;
	
	 default:
	 printf("Invalid choice\n>>");
	 break;
      }
     
      printf("Enter the no of 32-bit memory blocks to verify pattern\n>>");
      scanf("%d",&length);
      printf("Enter the seed value to generate the psudo-random patttern for verification\n>>");
      scanf("%d",&seed_value);

      j=(uint32_t *)malloc(8); 
 
      for(j=mem;j<=memlast;j++)		//Loop starts from the starting address of the first block of allocated \
					  memory to the starting add of the last block of allocated memory
      {
	 if(j==address)			//If j is equal to the address entered by the user, break from the loop
	 {
	   break;
	 }
	 else
	 {
	    k++;			//If j is not equal to address entered by user, increment k	
	 }
      }
      if(k==(size+1))			//Condition to check whether entered address is valid or not
      {
	 printf("Memory entered is not valid\nTRY again\n>>");
      }
      else if(length<=(size-(k-1)))	//Condition to check whether the entered block size is valid or not
      {
	 clock_t first= clock();	//Store the value of clock() in the variable first
	 for(l=0;l<length;l++)		//Get the pattern and verify it
	 {
	    pattern = Pattern_gen(seed_value,j);
	    if(*j != pattern)
	    {
	       printf("Wrong pattern found");
	       wrong[inc] = (uint64_t)j;
	       inc++;
	    }
	    j++;
	    wrong[inc]=0;
	 }
         clock_t second=clock();	//Store the value of clock() in the variable second
         printf("Verification Done\n");
         printf("Time taken to perform write pattern =%f seconds\
                \n",(double)(second-first)*1000/CLOCKS_PER_SEC); // The time taken to perform verify_pattern	
      }
      else
      {
	 printf("The number of blocks entered is invalid\n>>");
      }
   
      if(wrong[0]!=0)			//print address at which verify fails
      {   
         printf("Wrong addresses are\n");   
         while(wrong[inc1] != 0)
         {
            printf("%lx\n",wrong[inc1]);
            inc1++;
         }
	 printf("Type the function you would like to perform or type help to see the menu\n>>");
      }
      else
      {
         printf("Type help to see more options\n>>");
      }
   }
   return 0;
}





