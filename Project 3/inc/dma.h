/**********************************************************************************
* FILENAME	    :dma.h															  *
* DESCRIPTION	:Headers required by dma and function declarations.				  *
* AUTHOR NAME	:Puneet Bansal & Nachiket Kelkar								  *
* TOOLS USED	:Kinetis Design Studio											  *
***********************************************************************************/

#ifndef INC_DMA_H_
#define INC_DMA_H_

/* ------------------- Includes -------------------- */
#include <stdint.h>
#include "board.h"
#include "fsl_debug_console.h"

typedef struct
{
float min_val;
float max_val;
float log_output;
}logval;


/* ------------ Lookup table for log values -------------- */
logval lookup[]={ {0,1638.4,-1.30}, {1638.4,3276.8,-1}, {3276.8,4915.2,-0.82}, {4915.2,6553.6,-0.70}, {6553.6,8192, -0.60},
				{8192,9830.4,-0.52}, {9830.4,11468.8,-0.46}, {11468.8,13107.2,-0.4}, {13107.2,14745.6,-0.34}, {14745.6,16384,-0.3},
				{16384,18022.4,-0.26}, {18022.4,19660.8,-0.22}, {19660.8,21299.2,-0.19}, {21299.2,22937.6,-0.15}, {22937.6,24576,-0.12},
				{24576,26214.4,-0.10}, {26214.4,27852.8,-0.07}, {27852.8,29491.2,-0.05}, {29491.2,31129.6, -0.02}, {31129.6,32768,0}};

/* ------------ Function declarations -------------- */
void dma_init();
void dma_start();
float getlog(float);

#endif /* INC_DMA_H_ */
