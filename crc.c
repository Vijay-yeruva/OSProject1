#include "crc.h"

int fillCRCArray(){
    CRC[32] = 1;
    CRC[26] = 1;
    CRC[23] = 1;
    CRC[16] = 1;
    CRC[12] = 1;
    CRC[11] = 1;
    CRC[10] = 1;
    CRC[8] = 1;
    CRC[7] = 1;
    CRC[5] = 1;
    CRC[4] = 1;
    CRC[2] = 1;
    CRC[1] = 1;
    CRC[0] = 1;
}
int* encodecrc(int* frame, int size){

    for(int i = 0; i < size;i++ ){

    }
   
}

int checkerror(int* frame, int size){
    for(int i = 0; i < size;i++ ){

    }
}