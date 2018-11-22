/*
* @Author: zazu
* @Date:   2018-11-21 16:37:21
* @Last Modified by:   zazu
* @Last Modified time: 2018-11-21 23:23:33
*/
#ifndef READPNG_H
#define READPNG_H

#include <png.h>
#include <stdio.h>
#include <stdlib.h>

#include <image.h>

Image* readPNG(char* filename);
void savePNG(Image* image, char* filename);

#endif