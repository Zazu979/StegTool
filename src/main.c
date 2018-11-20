/*
* @Author: zazu
* @Date:   2018-11-20 15:00:41
* @Last Modified by:   zazu
* @Last Modified time: 2018-11-21 00:24:10
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdint.h>

#include <image.h>
#include <readPNG.h>
#include <compression.h>

int binToVal(int bin[8]){
   int ii, val = 0;

   for (ii = 0; ii < 8; ii++ ){
      val *= 2;
      val += bin[ii];   
   }

   return val;

}

void valToBin(int value, int bin[8]){
   int ii = 0, temp;
   
   for (ii = 0; ii < 8; ++ii){
      temp = value >> ii;
      bin[7-ii] = temp&1;
   }

}

void uint32ToBin(uint32_t value, int bin[32]){
   int ii, temp;

   for (ii = 0; ii < 32; ++ii){
      temp = value >> ii;
      bin[31-ii] = temp&1;
   }
}

void addBitToColour(int* colour, int binVal){
   if(*colour == 255 && binVal == 0)
      *colour = 255;

   if(*colour % 2 != binVal)
      *colour = *colour+1;  

}

void removeSteg(Image* image, char* outfile){
   int width = image->width;
   int height = image->height;
   Pixel* pixel;
   int ii,jj,kk;

   FILE* decompressedFile = fopen(DECOMPRESSED_FILE, "wb");

   int bin[8] = {0,0,0,0,0,0,0,0};

   uint32_t length = 0;
 
   int loops = 0;
   int count = 0;
   int value = 0;

   for (ii = 0; ii < height; ii++){
      for (jj = 0; jj < width; jj++){
         pixel = &(image->pixels[ii][jj]);
         for (kk = 0; kk < 3; kk++){
            if(count == 8){

               value = binToVal(bin);

               if(loops / 8 < 5){
                  length = length << 8;
                  length += value;
               }else{
                  fputc(value, decompressedFile);
               }

               /*Dont compare length until youve read it. And then you're done*/
               if(loops > 31 && loops == (length+4)*8){
                  fclose(decompressedFile);
                  decompressFile(DECOMPRESSED_FILE, outfile);
                  return;
               }

               count = 0;
            }

            bin[count] = pixel->rgb[kk]%2;
            count++;
            loops++;
         }
      }
   }
}

void startSteg(Image* image, char* filename, uint32_t fileLength){
   int width = image->width;
   int height = image->height;

   FILE* file = fopen(filename, "rb");

   Pixel* pixel;

   int curr;

   int binLength[32];

   int binValue[8] = {0,0,0,0,0,0,0,0};

   int loops = 0;

   int ii,jj,kk,idx = 0;

   uint32ToBin(fileLength, binLength);

   for (ii = 0; ii < height; ii++){
      for (jj = 0; jj < width; jj++){
         pixel = &(image->pixels[ii][jj]);
         for (kk = 0; kk < 3; kk++){
            /*Ok youre finally done*/
            if(loops == (fileLength+4)*8){ 
               fclose(file);
               return;
            }

            /*Finished Reading the file, now to write NULL*/
           /* if(loops == (fileLength+4)*8){
               printf("NEARLY DONE\n");
               fclose(file);
               file = NULL;
               valToBin(0, binValue);

               readFile = 0;

               idx = 0;
            }*/

            /*Dont read from file for the first 8 bytes*/
            if(loops >= 32){
               /*Read the next character and convert it to binary*/
               if(idx % 8 == 0){
                  /*fread(&curr, 1,1,file);*/
                  curr = fgetc(file);
                  valToBin(curr, binValue);
                  idx = 0;
               }

               addBitToColour(&pixel->rgb[kk], binValue[idx]);
               idx++;
            }
            else{
               addBitToColour(&pixel->rgb[kk], binLength[loops]);
            }

            loops++;
         }
      }
   }

   /*Shouldnt hit here, but just in case*/
   fclose(file);

}



int verifySize(Image* image, uint32_t inputLength){

   /*Input length isnt valid*/
   if(inputLength == 0)
      return -1;

   /*A single byte required 8 bits and 4 bytes are required to store the length
      The image can contain upto w*h*3 extra bits*/
   return (inputLength+4)*8 < (image->width * image->height * 3);

}

void printImage(Image* image){

}

int main(int argc, char **argv){
 
   if(argc == 4){
      char* imageFile = argv[1];
      char* textFile = argv[2];
      char* outfile = argv[3];
      Image* image= readPNG(imageFile);
      uint32_t inputLength;

      compressFile(textFile, COMPRESSED_FILE);
      inputLength = getFileLength(COMPRESSED_FILE);

      if(verifySize(image,inputLength)){
         startSteg(image, COMPRESSED_FILE, inputLength);
         removeSteg(image, outfile);
      }else{
         printf("Image file is not large enough to hide input file\n");
      }
      freeImage(image);
   }else{
      printf("./StegTool image.png input.txt output.png\n");
   }

   return 0;
}