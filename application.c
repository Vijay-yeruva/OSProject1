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
#include <string.h>

/******************************************************************************
* transforms a text file to an intermediate file
******************************************************************************/
void transmit(FILE* fin, FILE* fout){
    char buffer[BUFF_LEN+1] = {'\0'};
    while(1){
        int len = fread(buffer, sizeof(char), BUFF_LEN, fin);
        frameData(buffer, fout);
        memset(buffer, '\0', BUFF_LEN);
        if(len < BUFF_LEN)
            break;
    }
   
}
/******************************************************************************
* transforms an intermediate file to a text file
******************************************************************************/
void receive(FILE* fin, FILE* fout){
    char buffer[BUFF_LEN] = {'\0'};
    while (1)
    {
        int len = deframeData(fin, buffer, BUFF_LEN);
        fwrite(buffer, sizeof(char), len, fout);
        memset(buffer, '\0', BUFF_LEN);
        if(len == 0)
            break;
    }
}

