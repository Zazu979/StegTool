/*
 * @Author: Zazu
 * @Date:   2018-12-22 11:50:00
 * @Git:    https://github.com/Zazu979
 * @Last Modified by: Zazu
 * @Last Modified time: 2018-12-22 13:59:25
*/
 
#ifndef IMAGE_H
#define IMAGE_H

#define PIXEL_RED   0
#define PIXEL_GREEN 1
#define PIXEL_BLUE  2

#define RGB_IMAGE 1
#define GREY_IMAGE 0

#define HEADER_SIZE 32

// TODO refactor sizing here and store all options :)

typedef struct{
   unsigned int bitsPerColour : 1;  // Bits Per Pixel
   unsigned int compress      : 1;  // Whether the image data has been compressed
   unsigned int dataLength    : HEADER_SIZE -2 ; // The amount of data to to be read
   int binValue[HEADER_SIZE];       // Binary value of the  above information
   int binLength;                   // The number of bits that the header takes
}StegHeader;

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