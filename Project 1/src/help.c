/*
*********************************************************
FILENAME	:help.c
DESCRIPTION	:List of all functions with description
AUTHOR NAME	:Nachiket Kelkar & Puneet Bansal
TOOLS USED	:GCC, GNU MAKE			
*********************************************************
*/

#include<stdio.h>
#include<string.h>
#include "../inc/help.h"

int help()
{
printf("1)allocate       - allocate 32-bit blocks of memory\
      \n2)freee          - free the block of allocated memory\
      \n3)disp           - display the 32-bit blocks of memory\
      \n4)write          - write the 32-bit word to the memory location\
      \n5)invert         - invert the contents of the memory in memory location\
      \n6)write_pattern  - write a random pattern to the blocks of memory\
      \n7)verify_pattern - verify the contents of memory written by write_pattern\
      \n8)ext            - exit the utility\n>>");
return 0;
}
