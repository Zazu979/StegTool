/*
 * @Author: Zazu
 * @Date:   2018-12-22 11:51:48
 * @Git:    https://github.com/Zazu979
 * @Last Modified by: Zazu
 * @Last Modified time: 2018-12-22 15:52:15
*/


/*#include <stdint.h>*/

#include <stdio.h>
#include <stdlib.h>


#include <readJPG.h>
#include <readPNG.h>

#include <image.h>
#include <compression.h>
#include <binary.h>
#include <bool.h>
#include <genericSteg.h>

#include <createSteg.h>

static void hideBitInColour(int* colour, int binValue);
static int verifySize(Image* image, uint32_t inputLength);
static void startSteg(Image* image, char* filename, uint32_t fileLength);

void createSteganography(char* imageFile, char* inputFile, char* outputFile){

   uint32_t inputLength;
   Image* image = readImage(imageFile);

   // Returns the filename that is to be used, If the compression works then used the compressed one;
   // TODO error handling 
   inputFile = compressFile(inputFile, COMPRESSED_FILE);
   inputLength = getFileLength(inputFile);
   
   /*Check that the length can fit in the file*/
   if(verifySize(image,inputLength)){
      startSteg(image, inputFile, inputLength);
      saveImage(image, outputFile);
   }else{
      printf("Image file is not large enough to hide input file.\nImage has %d pixels. \
      You need atleast %d pixels. for this input file\n", image->width * image->height, ((inputLength+4)*8)/3);
   }

   /*Delete the temporary file*/
   remove(COMPRESSED_FILE);
   freeImage(image);
}

static StegHeader* createHeader(uint32_t fileLength, char* filename){
   
   int ii;
   
   StegHeader* header = (StegHeader*)malloc(sizeof(StegHeader));
   header->bitsPerColour = 0;

   /** 8 bits are needed for each byte of data in the file */
   header->dataLength = fileLength * 8;

   unsigned int dataLength = header->dataLength;

   // TODO enable the option to change bitsPerColour
   if(header->bitsPerColour == 0){
      header->binValue[0] = 0;
   }else{
      header->binValue[0] = 1;
   }

   if(filename == COMPRESSED_FILE){
      header->binValue[1] = TRUE;
   }else{
      header->binValue[1] = FALSE;
   }

   for(ii = HEADER_SIZE -1 ; ii > 1; ii--){
      header->binValue[ii] = dataLength & 1;
      dataLength >>= 1;
   }


   header->binLength = HEADER_SIZE;

   return header;
}



static void startSteg(Image* image, char* filename, uint32_t fileLength){
   int width = image->width;
   int height = image->height;

   FILE* file = fopen(filename, "rb");

   // TODO add error checking on file

   Pixel* pixel = NULL; 
   Pixel* prev = NULL;

   int ii,jj,kk,idx = 0, loops = 0;

   const int* rgbOrder = NULL;

   int requiredLoops;

   Bool readHeader = TRUE;

   unsigned char curr;
   int binValue[8] = {0,0,0,0,0,0,0,0};
   int bitValue = -1;

   StegHeader* header = createHeader(fileLength, filename);


   requiredLoops = (fileLength*8) + header->binLength;

   for(ii = 0; ii < height; ii++){
      for(jj = 0; jj < width; jj++){
         prev = pixel;
         rgbOrder = getOrder(prev);
         pixel = &(image->pixels[ii][jj]);
         for(kk = 0; kk < 3; kk++){

            // Yay the image has been modified, you can leave now.
            if(loops == requiredLoops){
               fclose(file);
               return;
            }

            if(readHeader){

               bitValue = header->binValue[idx];
               if(idx == header->binLength -1){
                  // You have finished the bits for the header-> Now onto the body
                  readHeader = FALSE;
                  // Reset the counter. -1 to counter the increment at the end of the loop
                  idx = -1;
               }
            }else{
               /** Youve finished with the current byte read from the file. Time to read the next
                *  one and reset the index of the Binary value
                */
               if(idx % 8 == 0){
                  curr = fgetc(file);
                  charToBin(curr, binValue);
                  // Start back at the beginning of the binary Array
                  idx = 0;
               }

               bitValue = binValue[idx];
            }

            hideBitInColour(&pixel->rgb[rgbOrder[kk]], bitValue);

            // prev = pixel;
            idx++;
            loops++;
         }
      }
   }

   /*Shouldnt hit here, but just in case*/
   fclose(file);
}

// static void hideBitInColour2(int* colour, int desiredValue, int bitSize){

//    int modVal = *colour % bitSize;
//    int bitValue = pow(bitSize,2);

//    if(modVal == desiredValue)
//       return;

//    /*Modify the colour by the minimum ammount possible. Go up or down the dependsing on the need.*/
//    if(modVal < desiredValue/2)
//       *colour = *colour + (desiredValue - modVal);
//    else
//       *colour = *colour + (desiredValue + modVal);

//    /*Handle limits*/
//    if(*colour > 255)   
//       *colour = *colour - bitValue;

//    if(*colour < 0)
//       *colour = *colour + bitValue;
// }

static void hideBitInColour(int* colour, int binValue){
   if(*colour == 255 && binValue == 0)
      *colour = 254;
   
   else if(*colour % 2 != binValue)
      *colour = *colour+1;  
}

static int verifySize(Image* image, uint32_t inputLength){

   /*Input length isnt valid*/
   if(inputLength == 0)
      return -1;

   /*A single byte required 8 bits and 4 bytes are required to store the length
      The image can contain upto w*h*3 extra bits*/
   return (inputLength+4)*8 < (image->width * image->height * 3);
}