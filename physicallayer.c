/******************************************************************************
* 
* Name: 	Vijay Yeruva
* Email: 	vyeruva@albany.edu
*
* physicallayer.c 
* Contains all the methods for the physical layer of data communication
*
******************************************************************************/

#include "physicallayer.h"


/******************************************************************************
* writes a char as a 8 char array of 0s and 1s
******************************************************************************/
void writeByte(char ch, FILE* fp)
{
    for (int i = BYTE_LEN-1; i >= 0; --i)
    {    
	    putc(ch & (1 << i) ? '1' : '0', fp);
    }
}

/******************************************************************************
* writes the char frame as a bit frame to the file given
******************************************************************************/
void writeBitFrame(char* frame, FILE* fp){
    int frameLegth = frame[2];
    int i = 0;
    for(i=0; i< 3; i++){
        writeByte(frame[i], fp);
    }
    for(i=3; i< frameLegth;i++)
    {
        writeByte(frame[i], fp);
    }
}


/******************************************************************************
* reads a 8 char array of 0s and 1s as a char
******************************************************************************/
char readByte(char** byte)
{
    char* buffer = *byte;
    char val = 0;
    for (int i = 0; i < BYTE_LEN; ++i)
    {
        val |= (buffer[i] & 1) << (7 - i);
    }
    return val;
}

/******************************************************************************
* reads the char frames from a file
******************************************************************************/
char* readBitFrame(FILE* fp){
    char byte[BYTE_LEN];
    char* frame = (char *)malloc(FRAME_LEN);
    memset(frame, '\0', FRAME_LEN);
    for(int i =0; i<FRAME_LEN; i++){
        int len = fread(byte, sizeof(char), BYTE_LEN, fp);
        if (len < BYTE_LEN)
            break;
        frame[i] = readByte(&byte);
    }
    return frame;
}