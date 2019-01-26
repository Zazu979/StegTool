/*
 * @Author: Zazu
 * @Date:   2018-12-22 11:51:25
 * @Git:    https://github.com/Zazu979
 * @Last Modified by: Zazu
 * @Last Modified time: 2019-01-26 18:53:13
*/

#include <stdio.h>
#include <stdlib.h>

#include <image.h>
#include <readPNG.h>
#include <readJPG.h>

Image* readImage(char* filename, IMAGE_TYPE type){

   if(type == PNG)
      return readPNG(filename);
   if(type == JPG)
      return readJPG(filename);

   return NULL;
}

void saveImage(Image* image, char* filename){

   IMAGE_TYPE type = detectImageType(filename);

   if(type == NOT_AN_IMAGE)
      perror("Output image is not an image type. Use PNG or JPG");
   else if(type == UNKNOWN_FORMAT)
      perror("Output image is not compatible. Change format");
   else{
      if(type == PNG)
         savePNG(image, filename);
      else if(type == JPG)
         saveJPG(image, filename);
   }

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