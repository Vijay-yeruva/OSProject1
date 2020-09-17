/******************************************************************************
* 
* Name: 	Vijay Yeruva
* Email: 	vyeruva@albany.edu
*
* constants.h
*
******************************************************************************/

#ifndef CONSTANTS_H
#define CONSTANTS_H

#define FAILURE 1
#define SUCCESS 0

#define BYTE_LEN 8
#define FRAME_LEN 67
#define HAMMING_LEN 7


#define CRC_LEN 33
#define FRAME_CRC_LEN 569

#define INT(ch)  ch - 48

#define ENCODE_NONE 0
#define ENCODE_CRC 1
#define ENCODE_HAMMING 2

#endif
