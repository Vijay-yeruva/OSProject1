#include "crc.h"
#include "constants.h"
#include <string.h>

char CRC[CRC_LEN] = "100000100100000010001110110110111";
char* encodecrc(char* data, int size){
    int length = CRC_LEN + size;
    char* framecrc = (char*)calloc(length, sizeof(char));
    memcpy(framecrc, data, size * sizeof (char));
    int j =0;
    while(j < size)
    {
        int i = 0;
        for(i = 32; i >=0; i-- )
        {
            framecrc[32-i+j] = (framecrc[32-i+j] != CRC[i])? '1':'0';
        }
        for(i = 0; i< size; i++)
        {
            if(framecrc[i] == '1')
            {
                break;
            }
        }
        j = i;
    }
    //copy data again so that the remainder is added at the end
    memcpy(framecrc, data, size * sizeof (char));
    return framecrc;
}

int checkcrcerror(char* data, int size){
    int length = size - CRC_LEN;
    char* framecrc = (char*)calloc(size, sizeof(char));
    memcpy(framecrc, data, length);
    int j =0;
    while(j < length)
    {
        int i = 0;
        for(i = 32; i >=0; i-- )
        {
            framecrc[32-i+j] = (framecrc[32-i+j] != CRC[i])? '1':'0';
        } 
        for(i = 0; i< size; i++)
        {
            if(framecrc[i] == '1')
            {
                break;
            }
        }
        j = i;
    }
    for(j =0; j < CRC_LEN; j++){
        if(data[length+j] != framecrc[length+j])
            return FAILURE;
    }
    return SUCCESS;
}