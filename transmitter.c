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
    fclose(fin);
    fclose(fbits);
    return 1;
}