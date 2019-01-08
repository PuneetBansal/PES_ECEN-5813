                                      PROJECT 2: CIRCULAR BUFFER, UART AND INTERRUPTS
                                                ECEN 5813, Fall 2018
                                                Professor: Kevin Gross
                                      Authors: Puneet Bansal and Nachiket Kelkar


                                                PROJECT DESCRIPTION
  
•	Implemented a circular buffer of characters with the following functionality.

   o	Ability to operate on multiple buffers of different size using the same code 
          
   o	Ability to add new item, delete oldest item, perform bound checking and reporting of errors in case of adding to a full buffer             and removing from an empty buffer 
  
•	Implemented C-Unit test framework on Linux platform to check the circular buffer functions

   o	Created an automated long running randomized test case 
  
•	Generated a Makefile that supports native compilation (HOST) and cross compilation (KL25Z and Beaglebone)

•	Wrote UART driver for both Blocking as well Non-Blocking Implementation  


                                                 FOLDER DETAILS
•	UNIT TEST FOLDER:  Contains CUnit test files to perform unit testing on circular buffer functions.
•	KL25Z UART: Contains source and header files for UART driver, circular buffer and application (Counting characters transmitted via UART, generation of report ) 

                                              HOW TO RUN THE PROGRAM
•	*make test1*                          : Generate test1 executable file for unit testing.
•	*make proj2*                          : Generate proj2 executable file for Linux platform to perform circular buffer functions
•	*make cross_compile PLATFORM=KL25z*   : Generate .elf file for KL25Z platform
•	*make cross_compile PLATFORM=BBB*     : Generate .elf file for Beaglebone Black
•	Type *./test1* is to run the unit test.
•	Type *./proj2* to run the circular buffer program


