/******************************************************************************
* 
* Name: 	Vijay Yeruva
* Email: 	vyeruva@albany.edu
*
* receiver.c
*
* This file implements receiver 
******************************************************************************/
#include "application.h"

int main(int argc, char* argv[]){
    FILE *fbits, *fout;
     int type = -1;
    if(argc < 2){
        printf("Please enter output file and encoding type as an argument\n");
        return 0;
    }
    else{
        type = argv[2][0] - 48;
        if(type < 0 || type > 2){
            printf("Encoding should be any of 0,1,2\n They mean None (0), CRC (1), HAMMING (2)");
        }
        fout = fopen(argv[1], "w"); 
    }
    fbits = fopen("Bits.txt", "r");
    receive(fbits, fout, type);
    fclose(fbits);
    fclose(fout);
    return 1;
}