/**********************************************************************************
* FILENAME	    :adc.h															  *
* DESCRIPTION	:Headers required by adc and function declarations.				  *
* AUTHOR NAME	:Puneet Bansal & Nachiket Kelkar								  *
* TOOLS USED	:Kinetis Design Studio											  *
***********************************************************************************/
#ifndef INC_ADC_H_
#define INC_ADC_H_

/* ------------------- Includes -------------------- */
#include <stdint.h>
#include "board.h"


/* ------------ Function declarations -------------- */
void adc_init();
uint32_t adc_read();
int adc_cal(void);

#endif /* INC_ADC_H_ */
