/*@file - memory.h
 *@brief - The implementation file for memory manipulation
 * This implementation file provides the function definitions for
 * copying data using pointers from one memory location to another,setting data, reversing the order of bytes
 * from certain memory locations.
 *@author Vipraja Patil & Nikhil Divekar
 *@date 3 October 2017
 */

#ifndef MEMORY_H_  
#define MEMORY_H_
#include <stdint.h>

/*
 *@brief - Memory move
 *This function takes two byte pointers (one source and one destination) 
 *and a length of bytes tocopy from the source location to the destination.
 *The behavior should handle overlap of source and destination. Copy should occur, with no data
 *corruption.
 *@param - * src: Source Pointer
 *@param - * dst: Destination Pointer
 *@param - length: Length of the bytes
 *@return a pointer to the destination
 */
uint8_t * my_memmove(uint8_t * src, uint8_t* dst, size_t length);


/*
 *@brief - Memory Copy
 *This function takes two byte pointers (one source and one destination) 
 *and a length of bytes tocopy from the source location to the destination.
 *The behavior is undefined if there is overlap of source and destination. Copy should still occur,
 *but will likely corrupt your data.
 *@param - * src: Source Pointer 
 *@param - * dst: Destination Pointer
 *@param - length: Length of the bytes
 *@return a pointer to the destination
 */	
uint8_t * my_memcpy(uint8_t * src, uint8_t * dst, size_t length);


/*
 *@brief - Set values to a location
 *This should take a pointer to a source memory location, a length in bytes and set all locations of
 *that memory to a given value.
 *@param - * src: Source Pointer
 *@param - length: Length of the bytes
 *@param - value: Value to be copied
 *@return a pointer to the source
 */
int8_t * my_memset(uint8_t * src, size_t, uint8_t);

	
/*
 *@brief - Set all the values zero
 *This function will take a pointer to a memory location, a length in bytes and zero out all of the
 *memory.
 *@param - * src: Source Pointer 
 *@param - length: Length of the bytes
 *@return a pointer to the source
 */	
uint8_t * my_memzero(uint8_t * src, size_t length);	


	
/*
 *@brief - Reversal of bytes
 *This function will take a pointer to a memory location and a length in bytes and reverse the order of
 *all of the bytes.
 *@param - * src: Source Pointer
 *@param - length: Length of the bytes
 *@return a pointer to the source
 */					
uint8_t * my_reverse(uint8_t * src, size_t length);			


/*
 *@brief - Reserve words
 *This function will take number of words to allocate in dynamic memory.
 *@param - length: Length of the bytes
 *@return a pointer to the allocation if successful or a NULL pointer if not successful
 */
int32_t * reserve_words(size_t length);


/*
 *@brief - Reserve words
 *This function will free a dynamic memory allocation by providing the pointer src
 *@param - * src: Source Pointer
 *@return void
 */			
void free_words(int32_t * src);				


#endif // MEMORY_H_

