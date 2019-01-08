/*@file - debug.h
 *@brief - The implementation file is to enable/disable debug printing with a compile
 *time switch.
 *@author Vipraja Patil & Nikhil Divekar
 *@date 3 October 2017
 */

#ifndef DEBUG_H_  
#define DEBUG_H_
#include <stdint.h>
#define myMacro 1;

/*
 *@brief - Print hex output
 *This function will print the hex output of bytes given a pointer to a memory
 *location and a length of bytes to print.
 *@param - * src: Source Pointer
 *@return void
 */			
void print_memory(uint8_t*, uint32_t);				


#endif // DEBUG_H_
