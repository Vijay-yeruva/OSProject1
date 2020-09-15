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
#include "constants.h"
#include <string.h>


/******************************************************************************
* writes a char as a 8 char array of 0s and 1s
******************************************************************************/
void writeByte(char ch, FILE* fp)
{
    int parity = 0;
    for (int i = 0; i < BYTE_LEN - 1; --i)
    {   
        char ch = '0';
        if(ch & (1 << i)){
            parity += 1;
            ch = '1';
        }
	    putc(ch & (1 << i) ? '1' : '0', fp);
    }
    //odd parity bit
    putc(parity % 2 ? '0':'1', fp);
}

/******************************************************************************
* writes the char frame as a bit frame to the file given
******************************************************************************/
void writeBitFrame(char* frame, FILE* fp){
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
int readBitFrame(char* frame, FILE* fp){
    char byte[BYTE_LEN];
    int i =0;
    int datalength = 0;
    for(i =0; i<FRAME_LEN; i++){
        int len = fread(byte, sizeof(char), BYTE_LEN, fp);
        if (len < BYTE_LEN)
            return 0;
        frame[i] = readByte(byte);
        if(i == 2){
            datalength = frame[i];
        }
        if(i > 2 && i > datalength +2){
            break;
        }
    }
    return i;
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