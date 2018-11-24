/*
* @Author: zazu
* @Date:   2018-11-20 15:00:41
* @Last Modified by:   zazu
* @Last Modified time: 2018-11-24 11:42:12
*/
/*
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdint.h>
*/

#include <string.h>

#include <readArgs.h>
#include <verbose.h>
#include <createSteg.h>
#include <destroySteg.h>

int main(int argc, char **argv){


   Arguments* args = readArgs(argc, argv);

   if(args != NULL){
      if(args->type == CREATE_STEG){

      }else if(args->type == DESTROY_STEG){

      }else{
         printf("Unknown error has occured\n");
      }
   }

   if(argc == 4){
      /*Desteg it*/
      if(strncmp(argv[1], "-d", 3) == 0){
         char* imageFile = argv[2];
         char* outputFile = argv[3];

         destroySteganography(imageFile, outputFile);
      }else{ /*Created Steg*/
         char* imageFile = argv[1];
         char* textFile = argv[2];
         char* outFile = argv[3];

         createSteganography(imageFile, textFile, outFile);
      }
   }else{
      printf("./StegTool image.png input.txt output.png\n");
      printf("./StegTool -d image.png input.txt \n");
   }

   return 0;
}