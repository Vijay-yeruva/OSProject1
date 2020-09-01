#include <stdio.h>
#include <stdlib.h>


int main()
{
   char ch, file_name[25],c;
   FILE *fp,*fp2;
   fp = fopen("ReadFile.txt", "r"); 
   fp2 = fopen("testout.txt", "w");
    
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
   return 0;
}
/*
code
Utsav Vohra <utsav2385@gmail.com>
Sat 15-02-2020 23:26


  #include <stdio.h>
  #include <string.h>
  #define MAX 256

  int main() {
        int num;
        FILE *fp1, *fp2;
        char ch, src[MAX], tgt[MAX];


         open the source file in read mode
        fp1 = fopen("ReadFile.txt", "r");

         error handling
        if (!fp1) {
                printf("Unable to open the input file!!\n");
                return 0;
        }

         open the target file in binary write mode
        fp2 = fopen("Test.out", "wb");

         error handling
        if (!fp2) {
                printf("Unable to open the output file!!\n");
                return 0;
        }

       
         * read data from input file and write
         * the binary form of it in output file
         
        while (!feof(fp1)) {
                 reading one byte of data
                fread(&ch, sizeof(char), 1, fp1);
                 converting the character to ascii integer value
                num = ch;
                 writing 4 byte of data to the output file
                fwrite(&num, sizeof(int), 1, fp2);
        }

        close all opened files
        fclose(fp1);
        fclose(fp2);
        return 0;
  }*/


