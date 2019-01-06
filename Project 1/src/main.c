/*
******************************************************************
FILENAME	:main.c
DESCRIPTION	:Contains the main body of the program
AUTHOR NAME	:Puneet Bansal & Nachiket Kelkar
TOOLS USED	:GCC, GNU MAKE		
******************************************************************
*/

#include <stdio.h>
#include <string.h>
#include "../inc/help.h"
#include "../inc/main.h"

typedef struct { char *ip; int (*funcp)();}lookup; //A structure to implement look up table

int main()
{
   int i=0;
   lookup table[]={{"help",&help},{"allocate",&allocate},{"write",&write},{"disp",&disp},\
                   {"freee",&freee},{"invert",&invert},{"ext",&ext},{"write_pattern",&write_pattern},\
                   {"verify_pattern",&verify_pattern}};
   char input[15];
   printf("Welcome to the command line \nType Help to see the commands\n>>");
   do
   {
      scanf("%s",input);
      for(i=0;i<9;i++)
      {
         if(strcmp(input,table[i].ip)==0)	//Check if user entered input is present in the look up table
         {
            (*table[i].funcp)();		//Call the function that user wants to perform
         }
      }

   }
   while(strcmp(input,"ext")!=0);		//Run the program till the time user enters ext
   return 0;
}

