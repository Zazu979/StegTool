/*
* @Author: zazu
* @Date:   2018-11-21 14:11:31
* @Last Modified by:   zazu
* @Last Modified time: 2018-11-21 23:14:08
*/

#ifndef DESTROYSTEG_H
#define DESTROYSTEG_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include <compression.h>
#include <image.h>
#include <binary.h>

void destroySteganography(char* imageFile, char* outputFile);
void removeSteg(Image* image, char* outfile);


#endif