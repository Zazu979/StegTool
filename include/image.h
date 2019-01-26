/*
 * @Author: Zazu
 * @Date:   2018-12-22 11:50:00
 * @Git:    https://github.com/Zazu979
 * @Last Modified by: Zazu
 * @Last Modified time: 2019-01-26 18:49:30
*/
 
#ifndef IMAGE_H
#define IMAGE_H

#include <fileType.h>

#define PIXEL_RED   0
#define PIXEL_GREEN 1
#define PIXEL_BLUE  2

#define RGB_IMAGE 1
#define GREY_IMAGE 0

#define HEADER_SIZE 32

// TODO refactor sizing here and store all options :)
// TODO fix bitSize 
typedef struct{
   unsigned int bitSize;      // Bits Per Pixel
   unsigned int compress;     // Whether the image data has been compressed
   unsigned int dataLength;   // The amount of data to to be read
   int binValue[HEADER_SIZE]; // Binary value of the  above information
}StegHeader;

typedef struct{
   int rgb[3];
}Pixel;

typedef struct{
   Pixel** pixels;
   int width, height;
}Image;

Image* readImage(char* filename, IMAGE_TYPE type);
void saveImage(Image* image, char* filename);
Image* createImage(int width, int height);
void freeImage(Image* image);


#endif