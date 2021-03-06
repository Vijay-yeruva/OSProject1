/******************************************************************************
* 
* Name: 	Vijay Yeruva
* Email: 	vyeruva@albany.edu
*
* datalinklayer.c
*
* This file implements data link layer function
******************************************************************************/

#include "physicallayer.h"
#include "datalinklayer.h"
#include "constants.h"
#include "crc.h"
#include <string.h>

/******************************************************************************
* Frames a null terminated char array into data frames and writes into file
******************************************************************************/
char* frameData(char* data, FILE* fp, int encodingType){
    char* buffer = data;
    char frame[FRAME_LEN] = {'\0'};
    int i =0;
    //divide the buffer into frames and write the bit frame
    while(*buffer != '\0'){
        if(i < 3)
        {
            frame[0] = 22;
            frame[1] = 22;
        }
        else
        {
            frame[i] = *buffer;
            buffer++;
        }

        if(i == FRAME_LEN -1)
        {
            frame[2] = i - 2;
            writeBitFrame(frame, fp, encodingType);
            memset(frame, '\0', FRAME_LEN);
            i = 0;
        }
        i++;
    }
    //if there are any extra frame left at the end should be written
    if(i > 1){
        frame[2] = i - 2;
        writeBitFrame(frame, fp, encodingType);
        memset(frame, '\0', FRAME_LEN);
        i = 0;
    }
}

/******************************************************************************
* Deframes dataframe from file and returns char array one frame at a time
******************************************************************************/
int deframeData(FILE* fp, char* data, int size, int encodingType){
    char* buffer = data;
    int end = feof(fp);
    int i = 0;
    while(i < size && !end)
    {
        char frame[FRAME_LEN] = {'\0'};
        int val = readBitFrame(frame, fp, encodingType);
        
        int len = frame[2];
        for(int j=0; j < len; j++){
           buffer[i] = frame[j+3];
           i++;
        }
        if(feof(fp)) //Reached end of bit file
           break;
    }
    return i;
}