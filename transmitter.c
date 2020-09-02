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

int main(){
    FILE *fin,*fbits;
    fin = fopen("Input.txt", "r"); 
    fbits = fopen("Bits.txt", "w");
    transmit(fin, fbits);
    fclose(fin);
    fclose(fbits);
    return 1;
}