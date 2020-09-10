/******************************************************************************
* 
* Name: 	Vijay Yeruva
* Email: 	vyeruva@albany.edu
*
* crc.h
*
******************************************************************************/


#ifndef CRC_H
#define CRC_H

#include <stdio.h>

int CRC[32] = {0};
int* encodecrc(int*, int);
int checkerror(int*, int);
#endif