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
    if(argc < 2){
        printf("Please enter input file as an argument\n");
        return 0;
    }
    else{
        fin = fopen(argv[1], "r"); 
    }
    
    fbits = fopen("Bits.txt", "w");
    transmit(fin, fbits);
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