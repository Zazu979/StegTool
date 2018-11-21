#ifndef IMAGE_H
#define IMAGE_H

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