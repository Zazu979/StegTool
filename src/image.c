/*
 * @Author: Zazu
 * @Date:   2018-12-22 11:51:25
 * @Git:    https://github.com/Zazu979
 * @Last Modified by:   Zazu
 * @Last Modified time: 2018-12-22 11:51:25
*/


#include <stdlib.h>
#include <image.h>
#include <readPNG.h>

Image* readImage(char* filename){
   return readPNG(filename);
}

void saveImage(Image* image, char* filename){
   savePNG(image, filename);
}

Image* createImage(int width, int height){

   int ii = 0;
   Image* image = (Image*)malloc(sizeof(Image));

   image->width = width;
   image->height = height;

   image->pixels = (Pixel**)malloc(sizeof(Pixel*) * height);
   for (ii = 0; ii < height; ii++){
      image->pixels[ii] = (Pixel*)malloc(sizeof(Pixel) * width);
   }

   return image;
}

void freeImage(Image* image){
   int ii = 0;
   for (ii = 0; ii < image->height; ii++){
      free(image->pixels[ii]);
   }
   free(image->pixels);
   free(image);
}