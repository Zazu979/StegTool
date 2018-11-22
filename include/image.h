/*
* @Author: zazu
* @Date:   2018-11-21 22:37:25
* @Last Modified by:   zazu
* @Last Modified time: 2018-11-22 14:57:27
*/
#ifndef IMAGE_H
#define IMAGE_H

#define PIXEL_RED   0
#define PIXEL_GREEN 1
#define PIXEL_BELU  2

typedef struct{
   int rgb[3];
}Pixel;

typedef struct{
   Pixel** pixels;
   int width, height;
}Image;

Image* readImage(char* filename);
void saveImage(Image* image, char* filename);
Image* createImage(int width, int height);
void freeImage(Image* image);


#endif