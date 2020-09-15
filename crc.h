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
#include <stdlib.h>
#include "constants.h"

char* encodecrc(char*, int);
int checkframeerror(char*, int);
#endif