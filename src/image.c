/*
* @Author: zazu
* @Date:   2018-11-20 19:39:19
* @Last Modified by:   zazu
* @Last Modified time: 2018-11-20 22:35:25
*/

#include <stdlib.h>
#include <image.h>

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