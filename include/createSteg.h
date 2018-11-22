/*
* @Author: zazu
* @Date:   2018-11-21 15:13:03
* @Last Modified by:   zazu
* @Last Modified time: 2018-11-22 10:42:30
*/

#ifndef CREATESTEG_H
#define CREATESTEG_H

/*
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
*/

#include <image.h>
#include <readPNG.h>
#include <compression.h>
#include <binary.h>

void createSteganography(char* imageFile, char* textfile,char* outputFile);


#endif