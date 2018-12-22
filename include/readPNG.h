/*
 * @Author: Zazu
 * @Date:   2018-12-22 11:51:41
 * @Git:    https://github.com/Zazu979
 * @Last Modified by:   Zazu
 * @Last Modified time: 2018-12-22 11:51:41
*/

#ifndef READPNG_H
#define READPNG_H

#include <image.h>

Image* readPNG(char* filename);
void savePNG(Image* image, char* filename);

#endif