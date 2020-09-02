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

#define BYTE_LEN 8
#define FRAME_LEN 67

void writeByte(char, FILE*);
void writeBitFrame(char*, FILE*);
char readByte(FILE*);
char* readBitFrame(FILE*);

#endif
