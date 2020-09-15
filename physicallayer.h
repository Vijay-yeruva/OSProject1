/******************************************************************************
* 
* Name: 	Vijay Yeruva
* Email: 	vyeruva@albany.edu
*
* physicallayer.h
*
******************************************************************************/

#ifndef PHYSICAL_LAYER_H
#define PHYSICAL_LAYER_H

#include <stdio.h>
#include <stdlib.h>
#include "errormodule.h"

void writeByte(char, FILE*);
char* writeByteToArray(char, char*);
void writeBitFrame(char*, FILE*);
char readByte(char*);
int readBitFrame(char*, FILE*);
int readCRCremainder(char*, FILE*);
int readBinaryFrame(char*, FILE*);

#endif
