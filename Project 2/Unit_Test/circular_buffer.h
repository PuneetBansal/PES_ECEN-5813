/*
***************************************************************************************************************************************
FILENAME	:circular_buffer.h
DESCRIPTION	:Contains the definitions related to circular buffer.
AUTHOR NAME	:Puneet Bansal & Nachiket Kelkar
TOOLS USED	:GCC, GNU MAKE	
****************************************************************************************************************************************
*/  

/*Including header files*/
  #include<stdio.h>
  #include<stdint.h>

/*Defining the structure for circular buffer*/
  typedef struct 
  {
    uint8_t *buffer;
    uint8_t *newbuffer;
    uint8_t *head;
    uint8_t *tail;
    uint8_t size;
    uint8_t count;
  }cb;

/*Enum for checking the status of the buffer after various functions*/
  typedef enum
  {
    cb_init_success=0,
    cb_init_fail,
    cb_empty,
    cb_not_empty,
    cb_full,
    cb_not_full,
    null_ptr,
    buffer_NA,
    cb_success
  }buffer_status;

/*Function definitions of the various circuar buffer functions*/
  buffer_status cb_init(cb *ptr, uint8_t buffer_length);
  buffer_status cb_add(cb *ptr, uint8_t element_to_add);
  buffer_status cb_delete(cb *ptr, uint8_t *element_deleted);
  buffer_status cb_isempty(cb *ptr);
  buffer_status cb_isfull(cb *ptr);
  buffer_status cb_resize(cb *ptr,uint8_t new_buffer_length);
