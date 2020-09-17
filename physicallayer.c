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
#include "crc.h"
#include "hammingcode.h"
#include "constants.h"
#include <string.h>

FILE* ferr = NULL;
/******************************************************************************
* writes a char as a 8 char array of 0s and 1s
******************************************************************************/
void writeByte(char ch, FILE* fp)
{
    int parity = 0;
    for (int i = 0; i < BYTE_LEN - 1; ++i)
    {   
        char bit = '0';
        if(ch & (1 << i)){
            parity += 1;
            bit = '1';
        }
	    putc(bit, fp);
    }
    //odd parity bit
    putc(parity % 2 ? '0':'1', fp);
}

/******************************************************************************
* writes the char frame as a bit frame to the file given
******************************************************************************/
void writeBitFrame(char* frame, FILE* fp, int encodingType){
    int frameLegth = frame[2];
    switch (encodingType)
    {
    case ENCODE_NONE: 
        for(int i=0; i< frameLegth+3;i++)
        {
            writeByte(frame[i], fp);
        }
        break;
    case ENCODE_CRC:
        writeBitFrameCRC(frame, fp);
        break;
    case ENCODE_HAMMING:
        writeBitFrameHamming(frame, fp);
        break;
    default:
        break;
    }
}

/******************************************************************************
* writes the char frame as a CRC encoded bit frame to the file given
******************************************************************************/
void writeBitFrameCRC(char* frame, FILE* fp){
    int frameLegth = frame[2];
    char* framebyte = (char*)malloc((frameLegth+3) * BYTE_LEN * sizeof(char));
    memset(framebyte, '0', (frameLegth+3) * BYTE_LEN );
    char* messagestart = framebyte;
    for(int i=0; i< frameLegth+3;i++)
    {
        framebyte = writeByteToArray(frame[i], framebyte);
    }
    char* data = messagestart;
    int size = (frameLegth+3)*8;
    char* framecrc = encodecrc(data, size);
    for(int i =0 ; i< size+CRC_LEN; i++){
        putc(framecrc[i], fp);
    }
    //free(framebyte);
    //free(framecrc);
}

/******************************************************************************
* writes the char frame as a hamming encoded bit frame to the file given
******************************************************************************/
void writeBitFrameHamming(char* frame, FILE* fp){
    int frameLegth = frame[2];
    for(int i=0; i< frameLegth+3;i++)
    {
        char bytearray[BYTE_LEN] = {'0'};
        writeByteToArray(frame[i], bytearray);
        char hammingcode[2*HAMMING_LEN] = {'0'};
        encodehamming(bytearray, hammingcode);
        for(int j = 0; j < 2*HAMMING_LEN; j++){
            putc(hammingcode[j], fp);
        }
    }
}

/******************************************************************************
* writes the char frame as a bit frame to a char array
******************************************************************************/
char* writeByteToArray(char data, char* array){
    int parity = 0;
    for (int i = 0; i < BYTE_LEN - 1; i++)
    {   
        char ch = '0';
        if(data & (1 << i)){
            parity += 1;
            ch = '1';
        }
	    *array = ch;
        array++;
    }
    //odd parity bit
    *array = parity % 2 ? '0' : '1';
    array++;
    return array;
}

/******************************************************************************
* reads a 8 char array of 0s and 1s as a char
******************************************************************************/
char readByte(char* byte)
{
    char* buffer = byte;
    char val = 0;
    for (int i = 0; i < BYTE_LEN-1; ++i)
    {
        val |= ((int)buffer[i] - 48) << i;
    }
    return val;
}

/******************************************************************************
* reads the char frames from a file
******************************************************************************/

int readBitFrame(char* frame, FILE* fp, int encodingType){
    char byte[BYTE_LEN];
    int i =0;
    if(encodingType == ENCODE_HAMMING){
        return readHammingBitFrame(frame, fp);
    }

    if(encodingType == ENCODE_CRC){
        checkFrameError(fp);
    }

    for(i=0; i<FRAME_LEN; i++){
        int len = fread(byte, sizeof(char), BYTE_LEN, fp);
        if (len < BYTE_LEN)
            return 0;
        frame[i] = readByte(byte);
    }
     
    if(encodingType == ENCODE_CRC){
        char remainder[33] = {'\0'};
        int rval = readCRCremainder(remainder, fp);
    }
    return i;
}

int checkFrameError(FILE* fp){
    char frameCRC[FRAME_CRC_LEN + 1] = {'\0'};
    long pos = ftell(fp);
    int val = readBinaryFrame(frameCRC, fp);
    if(val != -1)
    {
        val = checkcrcerror(frameCRC, val);
        if(val == FAILURE)
        {
            printf("Error in the frame: %s", frameCRC);
            return FAILURE;
        }
    }
    fseek(fp,pos,SEEK_SET);
}

/******************************************************************************
* reads the CRC remainder at the end of frames from a file
******************************************************************************/
int readCRCremainder(char* remainder, FILE* fp)
{
    char byte[33];
    int len = fread(byte, sizeof(char), CRC_LEN, fp);
    return len;
}


/******************************************************************************
* reads the frame including crc remainder as a binary char array from a file
******************************************************************************/
int readBinaryFrame(char* frame, FILE* fp)
{
    char byte[BYTE_LEN];
    int i =0;
    int datalength = 0;
    char* dest = frame;
    for(i =0; i<FRAME_LEN; i++){
        int len = fread(byte, sizeof(char), BYTE_LEN, fp);
        if (len < BYTE_LEN)
            return 0;
        memcpy(dest, byte, BYTE_LEN);
        dest += 8;
        if(i == 2){
            datalength = readByte(byte);
        }
        if(i > 2 && i > datalength+2){
            break;
        }
    }
    char crcremainder[CRC_LEN] = {'\0'};
    int len = fread(crcremainder, sizeof(char), CRC_LEN, fp);
    if(len < CRC_LEN){
        return -1;
    }
    memcpy(dest, crcremainder, CRC_LEN);
    int val = i * 8 + len;
    return val;

}

char readHammingByte(char* hammingcode)
{
    char buffer[BYTE_LEN] = {0};
    correcterrorsanddecode(hammingcode, buffer);
    char val = 0;
    for (int i = 0; i < BYTE_LEN-1; ++i)
    {
        val |= ((int)buffer[i] - 48) << i;
    }
    return val;

}

int readHammingBitFrame(char* frame, FILE* fp)
{
    char hammingcode[2*HAMMING_LEN];
    char buffer[BYTE_LEN];
    if(ferr == NULL)
    {
        ferr = fopen("error.txt", "w");
    }
    int i =0;
    for(i =0; i<FRAME_LEN; i++){
        int len = fread(hammingcode, sizeof(char), 2*HAMMING_LEN, fp);
        if (len < 2*HAMMING_LEN)
            return 0;
        decodehamming(hammingcode, buffer);
        char ch = readByte(buffer);
        if(i>2)
            fputc(ch, ferr);
        frame[i] = readHammingByte(hammingcode);
    }
    return i;
}