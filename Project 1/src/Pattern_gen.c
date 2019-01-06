
/*
**********************************************************************
FILENAME	:Pattern_gen.c
DESCRIPTION	:Function to generate the pattern
AUTHOR NAME	:Nachiket Kelkar & Puneet Bansal
TOOLS USED	:GCC, GNU MAKE			
**********************************************************************
*/

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include"../inc/Pattern_gen.h"

long Pattern_gen(int seed_value, uint32_t *addr)
{
   long pattern,addr_pattern;
   int x = seed_value, i=0, k=0;
   char str[50]={0};
   for(i=0;i<8;i++)
   {
      strcat(str, "f");
   }

/*Psudo random generator function*/
   pattern = 123*pow(x,10) + 17*pow(x,7) + 11*pow(x,3) + 9*pow(x,2) * 3;

/*Masking for 32-bit of word*/
   char mask[51] = {"0x"};
   strcat(mask, str);

   char *eptr;
   eptr=(char *)malloc(8);
   long mask1= strtol(mask, &eptr, 16);
 
/*Making of final patternwith use of memory location address*/  
   addr_pattern = mask1 & (uintptr_t)addr;
   pattern = mask1 & pattern;
   for(k=0;k<4;k++)
   {
      pattern = addr_pattern ^ pattern;
      addr_pattern = addr_pattern << 8;
   }
   pattern = addr_pattern ^ pattern;
   pattern = pattern & mask1;   
return pattern;
}
