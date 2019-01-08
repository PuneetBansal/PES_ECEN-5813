/**********************************************************************************
* FILENAME	    :adc.c															  *
* DESCRIPTION	:adc initialization and reading values from adc					  *
* AUTHOR NAME	:Nachiket Kelkar & Puneet Bansal								  *
* TOOLS USED	:Kinetis Design Studio											  *
***********************************************************************************/
#include "adc.h"

void adc_init()
{
	SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;							// Clock Gate to Port E
	SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;							// ADC0 clk enable
	ADC0_SC1A |= ADC_SC1_ADCH_MASK;

	//// Bus/2 clock selected, 16-bit, clock/8(3MHz)
	ADC0_CFG1 |= ADC_CFG1_ADICLK(1) | ADC_CFG1_MODE_MASK | ADC_CFG1_ADIV_MASK;
	ADC0_SC1A &= ~(ADC_SC1_AIEN_MASK);							// Interrupts disable,
	ADC0_SC1A |= ADC_SC1_DIFF_MASK;								// Differential mode, Disable ADC
	ADC0_SC2 |=  ADC_SC2_DMAEN_MASK;							// Enable the DMA with ADC

	// Continuous Conversion, Hardware avg
	ADC0_SC3 |= ADC_SC3_ADCO_MASK | ADC_SC3_AVGE_MASK | ADC_SC3_AVGS_MASK;
}

uint32_t adc_read()
{
	while(!(ADC0_SC1A & ADC_SC1_COCO_MASK));   			//wait for ADC conversion to finish
	return ADC0_RA;
}
