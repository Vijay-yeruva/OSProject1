/******************************************************************************
* 
* Name: 	Vijay Yeruva
* Email: 	vyeruva@albany.edu
*
* application.h
*
******************************************************************************/

#ifndef APPLICATION_H
#define APPLICATION_H

#include <stdio.h>

#define BUFF_LEN 256 

void transmit(FILE*, FILE*, int);
void receive(FILE*, FILE*, int);
#endif