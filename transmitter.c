/******************************************************************************
* 
* Name: 	Vijay Yeruva
* Email: 	vyeruva@albany.edu
*
* transmitter.c
*
* This file implements tranmitter 
******************************************************************************/
#include "application.h"
#include "errormodule.h"

int main(int argc, char* argv[]){
    FILE *fin,*fbits;
    int type = -1;
    if(argc < 3){
        printf("Please enter input file and encoding type as an argument\n");
        return 0;
    }
    else{
        type = argv[2][0] - 48;
        if(type < 0 || type > 2){
            printf("Encoding should be any of 0,1,2\n They mean None (0), CRC (1), HAMMING (2)");
        }
        fin = fopen(argv[1], "r"); 
    }
    
    fbits = fopen("Bits.txt", "w");
    transmit(fin, fbits, type);
    printf("How many errors you want to introduce?");
    int count = 0;
    scanf("%d", &count);
    if(count > 0)
    {
        errorlocation* locations = writeerrors(count, fbits);
        for(int i = 0; i<count; i++){
            printf("Frame: %d, Byte: %d, Bit: %d\n", locations[i].frame, locations[i].byte, locations[i].bit);
        }
    }
    fclose(fin);
    fclose(fbits);
    return 1;
}