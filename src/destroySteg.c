/*
* @Author: zazu
* @Date:   2018-11-21 14:07:26
* @Last Modified by:   zazu
* @Last Modified time: 2018-11-21 19:38:40
*/

#include <destroySteg.h>

void destroySteganography(char* imageFile, char* outputFile){
   Image* image = readImage(imageFile);
   removeSteg(image, outputFile);
}

void removeSteg(Image* image, char* outputFile){
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

               if(loops <= 32){
                  length = length << 8;
                  length += value;
               }else{
                  fputc(value, decompressedFile);
               }

               /*Dont compare length until youve read it. And then you're done*/
               if(loops > 31 && loops == (length+4)*8){
                  fclose(decompressedFile);
                  decompressFile(DECOMPRESSED_FILE, outputFile);
                  remove(DECOMPRESSED_FILE);
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

   /*Shouldnt hit here, but just in case*/
   fclose(decompressedFile);
   decompressFile(DECOMPRESSED_FILE, outputFile);
   remove(DECOMPRESSED_FILE);

}