/******************************************************************************
* 
* Name: 	Vijay Yeruva
* Email: 	vyeruva@albany.edu
*
* hammingcode.c
*
******************************************************************************/

#include "hammingcode.h"

/******************************************************************************
* This function encodes a byte length 0s and 1s array with hamming code bits
* Here (7,4) hamming code is implemented where every 4 bits are encoded.
* For hamming code even parity is considered. For a BYTE lenght the encoding is repeated once
******************************************************************************/
//*******************Parity calcualtion for 14 bit length********************/
//  0     1   2    3    4    5    6     7     8     9    10    11   12    13
//,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
//| D7 | D6 | D5 | P4 | D3 | P2 | P1 | D7' | D6' | D5' | P4' | D3' | P2' | P1' |
//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
//   
// P4 D5|D6|D7 => 3 2|1|0    P4' D5'|D6'|D7'  => 10 9|8|7
// P2 D3|D6|D7 => 5 4|1|0    P2' D3'|D6'|D7'  => 12 11|8|7
// P1 D3|D5|D7 => 6 4|2|0    P1' D3'|D5'|D7'  => 13 11|9|7 

int encodehamming(char* byte, char* encodedbyte)
{
    //First add the data bits
    for(int i = 0; i<BYTE_LEN; i++){
        if(i < HAMMING_LEN/2) 
            encodedbyte[i] = byte[i];
        if( i == HAMMING_LEN/2)
            encodedbyte[i+1] = byte[i];
        if(i > HAMMING_LEN/2 && i < BYTE_LEN -1)
            encodedbyte[i+3] = byte[i];
        if( i ==  BYTE_LEN - 1)
            encodedbyte[i+4] = byte[i];
    } 
    //Fill in the parity bits for odd parity
    encodedbyte[3] = (INT(encodedbyte[2]) + INT(encodedbyte[1]) + INT(encodedbyte[0])) % 2 ? '1' : '0';
    encodedbyte[5] = (INT(encodedbyte[4]) + INT(encodedbyte[1]) + INT(encodedbyte[0])) % 2 ? '1' : '0';
    encodedbyte[6] = (INT(encodedbyte[4]) + INT(encodedbyte[2]) + INT(encodedbyte[0])) % 2 ? '1' : '0';
    encodedbyte[10] = (INT(encodedbyte[9]) + INT(encodedbyte[8]) + INT(encodedbyte[7])) % 2 ? '1' : '0';
    encodedbyte[12] = (INT(encodedbyte[11]) + INT(encodedbyte[8]) + INT(encodedbyte[7])) % 2 ? '1' : '0';
    encodedbyte[13] = (INT(encodedbyte[11]) + INT(encodedbyte[9]) + INT(encodedbyte[7])) % 2 ? '1' : '0';
    return SUCCESS;
}

/******************************************************************************
* This function only decodes the hamming code without correcting it.
* This is only data bits are picked from hamming code ignoring the parity bits
******************************************************************************/
int decodehamming(char* hammingcode, char* byte)
{
     //Now add the data bits to bytes
    for(int i = 0; i<BYTE_LEN; i++){
        if(i < HAMMING_LEN/2) 
            byte[i] = hammingcode[i];
        if( i == HAMMING_LEN/2)
            byte[i] = hammingcode[i+1];
        if(i > HAMMING_LEN/2 && i < BYTE_LEN -1)
            byte[i] = hammingcode[i+3];
        if( i ==  BYTE_LEN - 1)
            byte[i] = hammingcode[i+4];
    } 

    return SUCCESS;
}

/******************************************************************************
* This function checks and corrects and then decodes a byte from the hamming code supplied
* Here (7,4) hamming code is implemented where every 4 bits are encoded
* Assumption the hamming code array is of size 14
******************************************************************************/
int correcterrorsanddecode(char* hammingcode, char* byte)
{
    int e1 = (INT(hammingcode[0]) + INT(hammingcode[1]) + INT(hammingcode[2]) + INT(hammingcode[3])) % 2;
    int e2 = (INT(hammingcode[0]) + INT(hammingcode[1]) + INT(hammingcode[4]) + INT(hammingcode[5])) % 2;
    int e3 = (INT(hammingcode[0]) + INT(hammingcode[2]) + INT(hammingcode[4]) + INT(hammingcode[6])) % 2;
    int errorpos = e1*4 + e2 *2 + e3*1;
    if(errorpos !=0)
    {
        char ch = hammingcode[7-errorpos];
        ch = ch == '0' ? '1' : '0';
         hammingcode[7-errorpos] = ch;
    }

    e1 = (INT(hammingcode[7]) + INT(hammingcode[8]) + INT(hammingcode[9]) + INT(hammingcode[10])) % 2;
    e2 = (INT(hammingcode[7]) + INT(hammingcode[8]) + INT(hammingcode[11]) + INT(hammingcode[12])) % 2;
    e3 = (INT(hammingcode[7]) + INT(hammingcode[9]) + INT(hammingcode[11]) + INT(hammingcode[13])) % 2;
    errorpos = e1*4 + e2 *2 + e3*1;
    if(errorpos !=0)
    {
        char ch = hammingcode[14-errorpos];
        ch = ch == '0' ? '1' : '0';
         hammingcode[14-errorpos] = ch;
    }

    //Now add the data bits to bytes
    for(int i = 0; i<BYTE_LEN; i++){
        if(i < HAMMING_LEN/2) 
            byte[i] = hammingcode[i];
        if( i == HAMMING_LEN/2)
            byte[i] = hammingcode[i+1];
        if(i > HAMMING_LEN/2 && i < BYTE_LEN -1)
            byte[i] = hammingcode[i+3];
        if( i ==  BYTE_LEN - 1)
            byte[i] = hammingcode[i+4];
    } 

    return SUCCESS;
}