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

/******************************************************************************
* Frames a null terminated char array into data frames and writes into file
******************************************************************************/
char* frameData(char** data, FILE* fp){
    char* buffer = *data;
    char frame[FRAME_LEN];
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
        }

        if(i == FRAME_LEN -1)
        {
            frame[2] = i - 2;
            writeBitFrame(&frame, fp);
            memset(frame, '\0', FRAME_LEN);
            i = 0;
        }
        else
        {
            i++;
            buffer++;
        }
    }
    //if there are any extra frame left at the end should be written
    if(i != 0){
        frame[2] = i - 2;
        writeBitFrame(&frame, fp);
        memset(frame, '\0', FRAME_LEN);
        i = 0;
    }
}

/******************************************************************************
* Deframes dataframe from file and returns char array one frame at a time
******************************************************************************/
int deframeData(FILE* fp, char** data, int size){
    char* buffer = *data;
    int i = 0;
    while(i< size)
    {
        char* frame = readBitFrame(fp);
        int len = frame[2];
        for(int j=3; j < len; j++){
           buffer[i] = frame[j];
           i++;
        }
    }
    return i;
}