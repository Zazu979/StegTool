/*
* @Author: zazu
* @Date:   2018-11-21 11:31:10
* @Last Modified by:   zazu
* @Last Modified time: 2018-11-21 19:39:22
*/

#include <createSteg.h>

static void addBitToColour(int* colour, int binVal);
static int verifySize(Image* image, uint32_t inputLength);
static void startSteg(Image* image, char* filename, uint32_t fileLength);

void createSteganography(char* imageFile, char* textFile, char* outputFile){

   uint32_t inputLength;
   Image* image = readImage(imageFile);

   compressFile(textFile, COMPRESSED_FILE);
   inputLength = getFileLength(COMPRESSED_FILE);
   
   /*Check that the length can fit in the file*/
   if(verifySize(image,inputLength)){
      startSteg(image, COMPRESSED_FILE, inputLength);

      saveImage(image, outputFile);

   }else{
      printf("Image file is not large enough to hide input file\n");
   }

   /*Delete the temporary file*/
   remove(COMPRESSED_FILE);
   freeImage(image);
}

static void startSteg(Image* image, char* filename, uint32_t fileLength){
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

   printf("Converting image to Steganography\n");
   for (ii = 0; ii < height; ii++){
      for (jj = 0; jj < width; jj++){
         pixel = &(image->pixels[ii][jj]);
         for (kk = 0; kk < 3; kk++){
            /*Ok you're finally done*/
            if(loops == (fileLength+4)*8){ 
               fclose(file);
               printf("\nImage has been converted\n");
               return;
            }

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
               /*For the first 32 bits input in the length into the image*/
               addBitToColour(&pixel->rgb[kk], binLength[loops]);
            }

            loops++;
         }
      }
   }

   /*Shouldnt hit here, but just in case*/
   fclose(file);
}

static void addBitToColour(int* colour, int binVal){
   if(*colour == 255 && binVal == 0)
      *colour = 254;
   
   else if(*colour % 2 != binVal)
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