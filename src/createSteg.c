/*
 * @Author: Zazu
 * @Date:   2019-01-26 15:14:34
 * @Git:    https://github.com/Zazu979
 * @Last Modified by: Zazu
 * @Last Modified time: 2019-01-26 18:52:05
*/



/*#include <stdint.h>*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <readJPG.h>
#include <readPNG.h>

#include <image.h>
#include <compression.h> 
#include <binary.h>
#include <bool.h>
#include <genericSteg.h>
#include <fileType.h>

#include <createSteg.h>

static void hideBitInColour(int* colour, int* binValue, int bitSize);
static int verifySize(Image* image, uint32_t inputLength, int bitSize);
static void startSteg(Image* image, char* filename, uint32_t fileLength, int bitSize);

void createSteganography(char* imageFile, char* dataFile, char* outputFile, int bitSize){

   uint32_t inputLength;

   IMAGE_TYPE imageType = detectImageType(imageFile);

   if(imageType == NOT_AN_IMAGE)
      perror("Input imagefile is not an image\n");
   else if(imageType == UNKNOWN_FORMAT)
      perror("Image type is not compatible. Please change\n");
   else{
      Image* image = readImage(imageFile, imageType);

      // Returns the filename that is to be used, If the compression works then used the compressed one;
      // TODO error handling 
      dataFile = compressFile(dataFile, COMPRESSED_FILE);
      inputLength = getFileLength(dataFile);
      
      /*Check that the length can fit in the file*/
      if(verifySize(image,inputLength, bitSize)){
         startSteg(image, dataFile, inputLength, bitSize);
         saveImage(image, outputFile);
      }else{
         printf("Image file is not large enough to hide input file.\nImage has %d pixels. \
         You need atleast %d pixels. for this input file\n", image->width * image->height, ((inputLength+4)*8)/3);
      }

      /*Delete the temporary file*/
      remove(COMPRESSED_FILE);
      freeImage(image);

   }
}

static StegHeader* createHeader(uint32_t fileLength, char* filename, int bitSize){
   
   int ii;
   
   StegHeader* header = (StegHeader*)malloc(sizeof(StegHeader));

   /** 8 bits are needed for each byte of data in the file */
   header->dataLength = fileLength * 8 / bitSize;

   unsigned int dataLength = header->dataLength;

   // TODO enable the option to change bitSize
   header->bitSize = 0;
   
   if(bitSize == 1){
      header->binValue[0] = 0;
   }else if(bitSize == 2){
      header->binValue[0] = 1;
   }else{
      perror("An unknown error has occured with the BitSize :(\n");
      header->bitSize = 1;
      header->binValue[0] = 0;
   }
   // Whether or not you have compressed the file
   if(filename - COMPRESSED_FILE == 0){
      header->binValue[1] = TRUE;
   }else{
      header->binValue[1] = FALSE;
   }

   for(ii = HEADER_SIZE -1 ; ii >= 2; ii--){
      header->binValue[ii] = dataLength & 1;
      dataLength >>= 1;
   }

   return header;
}

static void startSteg(Image* image, char* filename, uint32_t fileLength, int bitSize){
   int width = image->width;
   int height = image->height;

   FILE* file = fopen(filename, "rb");

   // TODO add error checking on file

   Pixel* pixel = NULL; 
   Pixel* prev = NULL;
   int* pixelColour;

   int ii,jj,kk,idx = 0, loops = 0;

   const int* rgbOrder = NULL;

   int requiredLoops;

   Bool readHeader = TRUE;

   unsigned char curr;
   int binValue[8] = {0,0,0,0,0,0,0,0};
   int* bitValue = NULL;
   StegHeader* header = createHeader(fileLength, filename, bitSize);

   requiredLoops = header->dataLength + HEADER_SIZE;

   // Set bitSize to 1 just for the header, then return back to value
   bitSize = 1;

   for(ii = 0; ii < height; ii++){
      for(jj = 0; jj < width; jj++){
         prev = pixel;
         rgbOrder = getOrder(prev);
         pixel = &(image->pixels[ii][jj]);
         for(kk = 0; kk < 3; kk++){

         // Yay the image has been modified, you can leave now.
            if(loops == requiredLoops){
               free(header);
               fclose(file);
               return;
            }

            if(readHeader){
               bitValue = &header->binValue[idx];
               if(idx == HEADER_SIZE - 1){
                  // You have finished the bits for the header-> Now onto the body
                  readHeader = FALSE;
                  // Reset the counter. -1 to counter the increment at the end of the loop
                  idx = -(header->bitSize + 1);

                  bitSize = header->bitSize +1;  //Need to add as as bitSize is either 0 or 1
               }
            }else{
               /** You've finished with the current byte read from the file. Time to read the next
                *  one and reset the index of the Binary value*/
               if(idx % 8 == 0){
                  curr = fgetc(file);
                  charToBin(curr, binValue);
                  // Start back at the beginning of the binary Array
                  idx = 0;
               }

               bitValue = &binValue[idx];
            }

            pixelColour = &pixel->rgb[rgbOrder[kk]];

            hideBitInColour(pixelColour, bitValue, bitSize);

            idx += bitSize;
            loops++;
         }
      }
   }

   /*Shouldnt hit here, but just in case*/
   fclose(file);
}

static void hideBitInColour(int* colour, int* binValue, int bits){

   if(bits == 1){
      if(*colour == 255 && *binValue == 0)
         *colour = 254;
      
      else if(*colour % 2 != *binValue)
         *colour = *colour+1; 
   }else if(bits == 2){
      int value = 0;

      // Convert the first 2 bits of the binary value into an integer
      if(binValue[0] == 1)
         value += 2;
      if(binValue[1] == 1)
         value += 1;
      
      // Get the mod value of the current colour
      int modVal = *colour % 4;

      // There is nothing to do if the colour already represents the value
      if(modVal == value)
         return;

      int modifier = value - modVal;

      // Go down by 1 instead of going up by 3. Reduce the maximum colour change
      if(modifier == 3)
         modifier = -1;

      *colour += modifier;

      // Boundary checks
      if(*colour < 0)
         *colour += 4;
      else if(*colour > 255)
         *colour -= 4;


   }else{
      // // The desired value to be stored
      // int value = 0;
      // int maxVal = 1;

      // for(int ii = 0; ii < bits; ii++){
      //    maxVal *= 2;
      //    value <<=1;
      //    value += binValue[ii];
      // }

      // int modVal = *colour % maxVal;

      // // You already have the desired value.
      // if(modVal == value)
      //    return;

      // int modifier = value - modVal;

      // // Modify up or down the minimum amount required
      // if(modifier > maxVal/2)
      //    modifier = modifier - maxVal;
      
      // *colour = *colour + modifier;

      // // Handle the boundary limits
      // if(*colour > 255)
      //    *colour -= maxVal;

      // if(*colour < 0)
      //    *colour += maxVal;

   }
}

static int verifySize(Image* image, uint32_t inputLength, int bitSize){

   /*Input length isnt valid*/
   if(inputLength == 0)
      return -1;

   /*A single byte required 8 bits and 4 bytes are required to store the length
      The image can contain upto w*h*3 extra bits*/
   return ((inputLength / bitSize)*8 + HEADER_SIZE) < (image->width * image->height * 3);
}