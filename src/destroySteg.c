/*
 * @Author: Zazu
 * @Date:   2018-12-22 11:47:20
 * @Git:    https://github.com/Zazu979
 * @Last Modified by: Zazu
 * @Last Modified time: 2018-12-22 15:25:27
 */
 

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include <compression.h>
#include <image.h>
#include <binary.h>
#include <genericSteg.h>
#include <bool.h>

#include <destroySteg.h> 

static void createHeader(StegHeader* header){
   // TODO allow for more than 2 bitSizes
   header->bitSize = header->binValue[0];
   header->compress = header->binValue[1];
   header->dataLength = 0;

   for(int ii = 2; ii < HEADER_SIZE; ii++){
      header->dataLength <<= 1;
      header->dataLength += header->binValue[ii];
   }

}

void destroySteganography(char* imageFile, char* outputFile){
   Image* image = readImage(imageFile);
   removeSteg(image, outputFile);
   freeImage(image);
}

void removeSteg(Image* image, char* outputFile){
   int width = image->width;
   int height = image->height;
   Pixel* pixel = NULL, *prev = NULL;
   int ii,jj,kk;

   // TODO error handling on file

   FILE* file = NULL;

   int binValue[8] = {0,0,0,0,0,0,0,0};

   const int* rgbOrder = NULL;
   
   Bool readHeader = TRUE;

   StegHeader* header = (StegHeader*)malloc(sizeof(StegHeader));

   int requiredLoops = -1;

   int bitValue = -1;

   int loops = 0;
   int idx = 0;
   unsigned char value = 0;

   // The value that the colour is modded by (Determined by bits per colour)
   int modder = 2; 
   int bitSize = 1;

   for (ii = 0; ii < height; ii++){
      for (jj = 0; jj < width; jj++){
         prev = pixel;
         rgbOrder = getOrder(prev);
         pixel = &(image->pixels[ii][jj]);
         for (kk = 0; kk < 3; kk++){

            if(loops == requiredLoops){

               fclose(file);

               if(header->compress == TRUE){
                  decompressFile(DECOMPRESSED_FILE, outputFile);
                  remove(DECOMPRESSED_FILE);
               }
               free(header);
               return;
            }

            bitValue = pixel->rgb[rgbOrder[kk]] % modder;

            if(readHeader){
               header->binValue[idx] = bitValue;

               if(idx == HEADER_SIZE -1){
                  readHeader = FALSE;
                  createHeader(header);
                  
                  requiredLoops = header->dataLength + HEADER_SIZE;

                  if(header->compress == TRUE){
                     file = fopen(DECOMPRESSED_FILE, "wb");
                  }else{
                     file = fopen(outputFile, "wb");
                  }

                  // TODO allow for more bitSizes
                  if(header->bitSize == 0){
                     bitSize = 1;
                     modder = 2;
                  }else{
                     bitSize = 2;
                     modder = 4;
                  }

                  idx = -bitSize;
               }
            }else{
                  for(int ii = bitSize-1; ii >= 0; ii--){
                     binValue[idx+ii] = bitValue % 2;
                     bitValue >>= 1;
                  }

                  if(idx == 8-bitSize){
                     value = binToVal(binValue);
                     fputc(value, file);
                     idx = -bitSize;                     
                  }
               }

            idx += bitSize;
            loops++;
         }
      }
   }

   //TODO also handle stuff here

}