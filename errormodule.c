#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "errormodule.h"
#include "constants.h"

errorlocation writeerror(FILE* fp){
    time_t t;
    errorlocation location; 
    location.bit = 0;
    location.byte = 0;
    location.frame = 0;
    srand((unsigned) time(&t));
    fseek(fp, 0L, SEEK_END); 
    long length = ftell(fp);
    long pos = rand() % length;
    location.frame = pos/FRAME_CRC_LEN + 1;
    location.byte = (pos % FRAME_CRC_LEN) / BYTE_LEN + 1;
    location.bit = (pos % FRAME_CRC_LEN) % BYTE_LEN;
    fseek(fp,pos,SEEK_SET);
    char ch = fgetc(fp);
    ch = ch == '0'? '1' : '0';
    fseek(fp,pos,SEEK_SET);
    fputc(ch, fp);
    return location;
}

errorlocation* writeerrors(int nooferrors, FILE* fp){
    errorlocation* errors = (errorlocation*)malloc(nooferrors * sizeof(errorlocation));
    for(int i = 0; i < nooferrors; i++){
        errorlocation location = writeerror(fp);
        errors[i] = location;
    }
    return errors;
}
