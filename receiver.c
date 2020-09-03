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
    if(argc < 2){
        printf("Please enter output file as an argument\n");
        return 0;
    }
    else{
        fout = fopen(argv[1], "w"); 
    }
    fbits = fopen("Bits.txt", "r");
    receive(fbits, fout);
    fclose(fbits);
    fclose(fout);
    return 1;
}