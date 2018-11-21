#ifndef CREATESTEG_H
#define CREATESTEG_H
/*
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
*/
#include <stdio.h>
#include <stdint.h>

#include <image.h>
#include <readPNG.h>
#include <compression.h>
#include <binary.h>

void createSteganography(char* imageFile, char* textfile,char* outputFile);

#endif