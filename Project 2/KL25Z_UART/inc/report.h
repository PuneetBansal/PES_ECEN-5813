/*****************************************************************************
* FILENAME		:report.h													 *
* DESCRIPTION	:Contain function declaration to print the report to screen	 *
* AUTHOR NAME	:Nachiket Kelkar & Puneet Bansal							 *
* TOOLS USED	:Kinetis Design Studio										 *
******************************************************************************/

#ifndef INC_REPORT_H_
#define INC_REPORT_H_

/* Including the header files */
#include <stdint.h>
#include "MKL25Z4.h"
#include "board.h"
#include <stdlib.h>
#include "uart.h"

/* Function declaration */
void generate_report(uint8_t*);

#endif /* INC_REPORT_H_ */
