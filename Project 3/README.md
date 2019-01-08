                                          PROJECT 3: ADC , DMA and DSP (FRDM KL25Z)
                                                    ECEN 5813, Fall 2018
                                                   Professor: Kevin Gross 
                                          Authors: Puneet Bansal and Nachiket Kelkar
___________________________________________________________________________________________________________________________________________
                                                  PROJECT DESCRIPTION:
                                                  
•	Set up on board Analog to Digital converter (ADC) on KL25Z with 16 bit resolution

      o	Configured processor pins 13 and 14 for use with differential mode channel 0 of ADC.

      o	Initially printed raw sample values to the UART.

      o	Later, configured the ADC to generate a DMA request.

•	 Configured DMA channel 0 to transfer the incoming samples from the ADC to a double buffer (64 sample size). The double buffer enables half of the buffer to be used by the processor and the other part to be used to bring in new ADC samples.
      
      o	Set up the source address as the ADC data register with no address update
      
      o	Set up the destination address as the 0th or the 64th position of the buffer (depending upon which part of the buffer to update) with address increment after each transfer
      
      o	Set up the byte transfer size as 128 bytes (64 samples * 2 bytes per sample)
      
      o	Configured DMA controller to generate an interrupt after a buffer worth of data is transferred. 

•	Wrote an application that examines each sample in the buffer and performs peak level metering on the data.

      o	Calculated peak values for each buffer and implemented look up table to report signal levels in dBFS units via UART.
___________________________________________________________________________________________________________________________________________
                                                   FOLDER DESCRIPTION
•	inc : contains all *.h* files

•	src : contains all *.c* files
