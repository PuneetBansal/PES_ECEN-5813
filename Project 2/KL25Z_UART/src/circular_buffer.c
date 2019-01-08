/*********************************************************************************
* FILENAME	    :circular_buffer.c									  		     *
* DESCRIPTION	:Contains the functions related to circular buffer.              *
* AUTHOR NAME	:Puneet Bansal & Nachiket Kelkar                                 *
* TOOLS USED	:Kinetis Design Studio                                           *
**********************************************************************************/

/*Header Files */
#include "circular_buffer.h"

/*Function to initialise the circular buffer.
If the received pointer object is null, it returns a null_ptr error.
else it allocates the buffer with the given buffer length, initialises count to 0
and sets the head and tail pointer to the buffer pointer.
*/
buffer_status cb_init(cb *ptr, uint16_t buffer_length)
{
	buffer_status status;

	if(ptr==NULL || buffer_length <=0)
    {
		status=null_ptr;
    }
	else
    {
		if(NULL==(ptr->buffer))
		{
			ptr->head=NULL;
			ptr->tail=NULL;
			ptr->count=0;
			ptr->size=0;
			status=cb_init_fail;
		}
		else
		{
			ptr->buffer= (uint8_t*)malloc(sizeof(uint8_t)*buffer_length);
			ptr->size= buffer_length;
			ptr->count=0;
			ptr->head=ptr->buffer;
			ptr->tail=ptr->buffer;
			status=cb_init_success;
		}
    }
	return status;
}


/*Function to check whether the circular buffer is full
returns cb_full status , if the buffer is full
*/
buffer_status cb_isfull(cb *ptr)
{
	buffer_status status;
	if(ptr==NULL)
	{
		status=null_ptr;
    }
	else if ((ptr->buffer)==NULL)
    {
		status=buffer_NA;
    }
	else if ((ptr->count)==(ptr->size))
    {
		status=cb_full;
    }
	else
    {
		status=cb_not_full;
    }
	return status;
}

/*Function to check whether the circular buffer is empty
returns cb_empty status , if the buffer is empty
*/
buffer_status cb_isempty(cb *ptr)
{
	buffer_status status;
	if(ptr==NULL)
    {
		status=null_ptr;
    }
	else if ((ptr->buffer)==NULL)
    {
		status=buffer_NA;
    }
	else if ((ptr->count)==0)
    {
		status=cb_empty;
    }
	return status;
}

/*Function to add element into the circular buffer.
The new element is added and the head is incremented.
If the head reached the max size of buffer, it gets wrapped around to the first location.
the function returns cb_success status on successful addition of the element.
*/
buffer_status cb_add(cb *ptr, uint8_t element_to_add)
{
	buffer_status status;
	if(ptr==NULL)
    {
		status=null_ptr;
    }
	else if ((ptr->buffer)==NULL)
    {
		status=buffer_NA;
    }
	else if (cb_isfull(ptr)==4)
    {
		status=cb_full;
    }
	else if(ptr->head==((ptr->buffer)+((ptr->size)-1)))
    {
		*(ptr->head)= element_to_add;
		ptr->head=ptr->buffer;
		ptr->count++;
		status=cb_success;
    }
	else
    {
		*(ptr->head)=element_to_add;
		ptr->head++;
		ptr->count++;
		status=cb_success;
    }
	return status;
}

/*Function to delete element from the circular buffer.
The element is added from the tail and the tail is incremented.
If the tail reached max size of buffer, it gets wrapped around to the first location.
the function returns cb_success status on successful deletion of the element.
*/
buffer_status cb_delete(cb *ptr, uint8_t *element_deleted)
{
	buffer_status status;
	if(ptr==NULL)
    {
		status=null_ptr;
    }
	else if ((ptr->buffer)==NULL)
    {
		status=buffer_NA;
    }
	else if (cb_isempty(ptr)==2)
    {
		status=cb_empty;
    }
	else if(ptr->tail==((ptr->buffer)+((ptr->size)-1)))
    {
		*(element_deleted)=*(ptr->tail);
		ptr->tail=ptr->buffer;
		ptr->count--;
		status=cb_success;
    }
	else
    {
		*(element_deleted)=*(ptr->tail);
		ptr->tail++;
		ptr->count--;
		status=cb_success;
    }
	return status;
}

/*Function to resize the buffer on runtime.
Increases the size of an already existing buffer
*/
buffer_status cb_resize(cb *ptr,uint8_t new_buffer_length)
{
	buffer_status status;
	if(ptr==NULL)
    {
		status=null_ptr;
    }
	else if ((ptr->buffer)==NULL)
    {
		status=buffer_NA;
    }
	else
    {
		ptr->newbuffer=(uint8_t *)realloc(ptr->buffer,sizeof(uint8_t)*new_buffer_length);
		ptr->buffer=ptr->newbuffer;
		ptr->size=new_buffer_length;
		status=cb_success;
    }
	return status;
}
