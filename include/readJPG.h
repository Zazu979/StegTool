/*
 * @Author: Zazu
 * @Date:   2018-12-22 11:51:38
 * @Git:    https://github.com/Zazu979
 * @Last Modified by:   Zazu
 * @Last Modified time: 2018-12-22 11:51:38
*/


#ifndef READJPG_H
#define READJPG_H

#include <image.h>

Image* readJPG(char* filename);
void saveJPG(Image* image, char* filename);

#endif