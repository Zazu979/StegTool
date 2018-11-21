#ifndef READPNG_H
#define READPNG_H

#include <png.h>
#include <stdio.h>
#include <stdlib.h>

#include <image.h>


Image* readPNG(char* filename);
void savePNG(Image* image, char* filename);

#endif