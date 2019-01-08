/*
***************************************************************************************************************************************
FILENAME	:test.c
DESCRIPTION	:Implementation of CUnit testing for circular buffer functions.
AUTHOR NAME	:Puneet Bansal & Nachiket Kelkar
TOOLS USED	:GCC, GNU MAKE	
****************************************************************************************************************************************
*/

/* Include Header Files*/


#include <stdio.h>
#include <CUnit/CUnit.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include "circular_buffer.h"
#include <time.h>


/* Pointer to the file used by the tests. */
static FILE* temp_file = NULL;


/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */

int init_suite1(void)
{
   if (NULL == (temp_file = fopen("temp.txt", "w+"))) {
      return -1;
   }
   else {
      return 0;
   }
}

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite1(void)
{
   if (0 != fclose(temp_file)) {
      return -1;
   }
   else {
      temp_file = NULL;
      return 0;
   }
}

/* Simple test of cb_init().
 * Calls the cb_init() function
 * and checks whether a sucess status 
 * is returned
*/

void test_cb_init(void)
{
buffer_status stat;
cb *tx_buffer;
tx_buffer=malloc(sizeof(cb));

CU_ASSERT_NOT_EQUAL((cb_init(tx_buffer,10)),0); 	//test should be true, since tx_buffer->buffer is NULL, so the return value of cb_init() will not be 0

tx_buffer->buffer=malloc(sizeof(uint8_t)*10);

CU_ASSERT_EQUAL((cb_init(tx_buffer,10)),0);    		//test should be true, since all valid conditions are satisfied.

}


/* Simple test of cb_add().
 * Initialises a buffer of size 10
 * Adds 10 elements and checks the status 
 * Adds 11th element and checks the status
*/

void test_cb_add(void)
{
int i;
cb *tx_buffer;
tx_buffer=malloc(sizeof(cb));
tx_buffer->buffer=malloc(sizeof(uint8_t)*10);
cb_init(tx_buffer,10);
for(i=0;i<10;i++)
	{
	CU_ASSERT_EQUAL((cb_add(tx_buffer,i)),8);
	}
cb_add(tx_buffer,11);
CU_ASSERT_NOT_EQUAL((cb_add(tx_buffer,i)),8);

}


/* Simple test of cb_delete().
 * Initialises a buffer of size 10
 * Adds 10 elements, deletes them and checks the status each time 
 * deletes 11th element and checks the status
*/

void test_cb_delete(void)
{
int i;
uint8_t* ed;
cb *tx_buffer;
tx_buffer=malloc(sizeof(cb));
tx_buffer->buffer=malloc(sizeof(uint8_t)*10);
cb_init(tx_buffer,10);
for(i=0;i<10;i++)
	{
	cb_add(tx_buffer,i);
	}

for(i=0;i<10;i++)
	{
	CU_ASSERT_EQUAL(cb_delete(tx_buffer,ed),8);
	}
CU_ASSERT_NOT_EQUAL(cb_delete(tx_buffer,ed),8);
}

/* Simple test of cb_isempty().
 * Initialises a buffer of size 10
 * Checks whether the buffer is empty
 * Adds 10 elements, deletes them and then checks for empty condition
 * deletes 10 elements and checks the empty condition
*/
void test_cb_isempty(void)
{
int i;
uint8_t* ed;
cb *tx_buffer;
tx_buffer=malloc(sizeof(cb));
tx_buffer->buffer=malloc(sizeof(uint8_t)*10);
cb_init(tx_buffer,10);

CU_ASSERT_EQUAL(cb_isempty(tx_buffer),2);
for(i=0;i<10;i++)
	{
	cb_add(tx_buffer,i);
	}
CU_ASSERT_NOT_EQUAL(cb_isempty(tx_buffer),2);

for(i=0;i<10;i++)
	{
	cb_delete(tx_buffer,ed);
	}
CU_ASSERT_EQUAL(cb_isempty(tx_buffer),2);
}

/* Simple test of cb_isempty().
 * Initialises a buffer of size 10
 * Checks whether the buffer is empty
 * Adds 10 elements, deletes them and then checks for empty condition
 * deletes 10 elements and checks the empty condition
*/
void test_cb_isfull(void)
{
int i;
uint8_t* ed;
cb *tx_buffer;
tx_buffer=malloc(sizeof(cb));
tx_buffer->buffer=malloc(sizeof(uint8_t)*10);
cb_init(tx_buffer,10);

CU_ASSERT_NOT_EQUAL(cb_isfull(tx_buffer),4);
for(i=0;i<10;i++)
	{
	cb_add(tx_buffer,i);
	}
CU_ASSERT_EQUAL(cb_isfull(tx_buffer),4);

for(i=0;i<10;i++)
	{
	cb_delete(tx_buffer,ed);
	}
CU_ASSERT_NOT_EQUAL(cb_isfull(tx_buffer),4);
}

/* Simple test of random().
 * Initialises a buffer of random size
 * Checks for status of initialisation
 * adds 0 to a randomly generated number in the buffer and checks status.
 * checks whether the buffer is full or not
 * deletes 10 elements and checks the status
*/
void test_random(void)
{
int i;
srand(time(0));
uint8_t* ed;
cb *tx_buffer, *check;
uint8_t rand_buff_size;
buffer_status stat;
rand_buff_size=(rand()%256);
tx_buffer=malloc(sizeof(cb));
tx_buffer->buffer=malloc(sizeof(uint8_t)*rand_buff_size);
CU_ASSERT_EQUAL(cb_init(tx_buffer,rand_buff_size),0);


for(i=0;i<(rand()%256);i++)
	{
	CU_ASSERT_EQUAL(cb_add(tx_buffer,i),8);
	}
CU_ASSERT_EQUAL(cb_isfull(tx_buffer),4);

for(i=0;i<(rand()%256);i++)
	{
	CU_ASSERT_EQUAL(cb_delete(tx_buffer,ed),8);
	}

}



int main()
{
   CU_pSuite pSuite = NULL;
   srand(time(0));
   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }


   if ((NULL == CU_add_test(pSuite, "test of cb_init()", test_cb_init)) ||(NULL == CU_add_test(pSuite, "test of cb_add()", test_cb_add)) || (NULL == CU_add_test(pSuite, "test of cb_delete()", test_cb_delete)) || (NULL == CU_add_test(pSuite, "test of cb_isempty()", test_cb_isempty)) || (NULL == CU_add_test(pSuite, "test of cb_isfull()", test_cb_isfull)) || (NULL == CU_add_test(pSuite, "test of random", test_random)))
   {
      CU_cleanup_registry();
      return CU_get_error();
   }


   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}

