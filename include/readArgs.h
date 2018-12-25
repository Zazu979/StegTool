/*
 * @Author: Zazu
 * @Date:   2018-12-22 11:51:32
 * @Git:    https://github.com/Zazu979
 * @Last Modified by:   Zazu
 * @Last Modified time: 2018-12-22 11:51:32
*/


#ifndef READARGS_H
#define READARGS_H

#include <bool.h>
//comment

typedef enum{CREATE_STEG, DESTROY_STEG} ARG_TYPE;

typedef enum{VALID, NO_IMAGE_FILE, NO_OUTPUT_FILE, NO_INPUT_FILE} ARG_STATUS;

typedef struct{
   char* imageFile;
   char* inputFile;
   char* outputFile;
   int bitSize; 
   Bool verbose;
   ARG_TYPE type;

   ARG_STATUS status;
}Arguments;

Arguments* readArgs(int argc, char** argv);

#endif