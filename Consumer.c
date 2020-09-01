
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
char			inputBuffer[8];
char			temp;
FILE *binin,*binout;
int				i;

binin = fopen("testout.txt", "r");
binout = fopen("ConsumerTest.txt", "w");
if (binin == NULL)
    exit(1);
if (!binout) {
                printf("Unable to open the output file!!\n");
                return 0;
        }
do
{
    int nIn = fread(inputBuffer, sizeof(char), sizeof inputBuffer, binin);
    if (nIn < sizeof inputBuffer)
    break;
    temp = 0;
    for (i = 0; i < 8; ++i)
    {
        temp |= (inputBuffer[i] & 1) << (7 - i);
    }
    putc(temp,binout);
} while(1);
printf("\n");
}

/*
int main()
{
   char ch, file_name[25],c;
   FILE *fp,*fp2;
   fp = fopen("ReadFile.txt", "r"); 
   fp2 = fopen("Test11.txt", "w");
    
   if (fp == NULL)
   {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   }
if (!fp2) {
                printf("Unable to open the output file!!\n");
                return 0;
        }
   while((ch = fgetc(fp)) != EOF){
        //printf("%c", ch);
	putc(' ',fp2);
for (int i = 7; i >= 0; --i)
    {   
        
	putc(ch & (1 << i) ? '1' : '0',fp2);
    }

       
   }
   fclose(fp);	
fclose(fp2);
*/
