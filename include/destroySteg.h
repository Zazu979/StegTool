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