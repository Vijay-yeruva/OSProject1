/******************************************************************************
* 
* Name: 	Vijay Yeruva
* Email: 	vyeruva@albany.edu
*
* error.h
*
******************************************************************************/

#ifndef ERROR_MODULE_H
#define ERROR_MODULE_H

typedef struct location{
    int frame;
    int byte;
    int bit;
} errorlocation;

errorlocation writeerror(FILE*);
errorlocation* writeerrors(int, FILE*);
#endif