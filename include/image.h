#ifndef IMAGE_H
#define IMAGE_H

typedef struct{
   int rgb[3];
}Pixel;

typedef struct{
   Pixel** pixels;
   int width, height;
}Image;


Image* createImage(int width, int height);
void freeImage(Image* image);
#endif