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

int main(){
    FILE *fbits, *fout;
    fbits = fopen("Bits.txt", "r");
    fout = fopen("Output.txt", "w");
    receive(fbits, fout);
    fclose(fbits);
    fclose(fout);
    return 1;
}