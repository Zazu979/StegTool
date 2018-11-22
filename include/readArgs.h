/*
* @Author: zazu
* @Date:   2018-11-22 10:37:46
* @Last Modified by:   zazu
* @Last Modified time: 2018-11-22 11:15:12
*/
#ifndef READARGS_H
#define READARGS_H

typedef enum{CREATE_STEG, DESTROY_STEG}TYPE;

typedef struct{
   char* imageFile;
   char* inputFile;
   char* outputFile;
   int verbose;
   TYPE type;
}Arguments;

void readArgs(int argc, char** argv);


#endif