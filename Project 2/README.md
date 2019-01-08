                                      PROJECT 2: CIRCULAR BUFFER, UART AND INTERRUPTS
                                                ECEN 5813, Fall 2018
                                                Professor: Kevin Gross
                                      Authors: Puneet Bansal and Nachiket Kelkar

******************************************************************************************************************************************
                                           **Project Description**
•	Implemented a circular buffer of characters with the following functionality 
  o	Ability to operate on multiple buffers of different size using the same code 
  o	Ability to add new item, delete oldest item, perform bound checking and reporting of errors in case of adding to a full buffer and         removing from an empty buffer 
•	Implemented C-Unit test framework on Linux platform to check the circular buffer functions
  o	Created an automated long running randomized test case 
•	Generated a Makefile that supports native compilation (HOST) and cross compilation (KL25Z and Beaglebone)
•	Wrote UART driver for both Blocking as well Non-Blocking Implementation  

******************************************************************************************************************************************



Unit Test folder contains files for running CUnit test. 
Use ./test1 is to run the unit test.
Use ./-proj2 to run the circular buffer program
