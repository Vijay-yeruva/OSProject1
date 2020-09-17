/******************************************************************************
* 
* Name: 	Vijay Yeruva
* Email: 	vyeruva@albany.edu
*
* datalinklayer.h
*
******************************************************************************/

#ifndef DATA_LINK_LAYER_H
#define DATA_LINK_LAYER_H

#include <stdio.h>

char* frameData(char*, FILE*, int);
int deframeData(FILE*, char*, int, int);
#endif