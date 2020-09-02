/******************************************************************************
* 
* Name: 	Vijay Yeruva
* Email: 	vyeruva@albany.edu
*
* application.c
*
* This file implements application layer functions
******************************************************************************/

#include "application.h"
#include "datalinklayer.h"

/******************************************************************************
* transforms a text file to an intermediate file
******************************************************************************/
void transmit(FILE* fin, FILE* fout){
    char* buffer[BUFF_LEN] = {'\0'};
    int len = fread(buffer, sizeof(char), BUFF_LEN, fin);
    frameData(&buffer, fout);
}
/******************************************************************************
* transforms an intermediate file to a text file
******************************************************************************/
void receive(FILE* fin, FILE* fout){
    char* buffer[BUFF_LEN] = {'\0'};
    int len = deframeData(fin, &buffer, BUFF_LEN);
    fwrite(buffer, sizeof(char), len, fout);
}