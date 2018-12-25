/*
 * @Author: Zazu
 * @Date:   2018-12-22 11:51:55
 * @Git:    https://github.com/Zazu979
 * @Last Modified by: Zazu
 * @Last Modified time: 2018-12-22 18:59:38
*/

/*
#include <unistd.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
*/
#include <stdlib.h>

#include <string.h>

#include <readJPG.h>  

#include <readArgs.h>
#include <verbose.h>
#include <createSteg.h>
#include <destroySteg.h>

#include <encryption.h>

int main(int argc, char **argv){

   encrypt("txt/test.txt", "txt/enc.txt", "HelloWorld");

   return 0;

   Arguments* args = readArgs(argc, argv);

   if(args->status == VALID){

      setVerbose(args->verbose);

      if(args->type == CREATE_STEG){
         createSteganography(args->imageFile, args->inputFile, args->outputFile);
      }else if(args->type == DESTROY_STEG){
         destroySteganography(args->imageFile, args->outputFile);
      }else{
         printf("Unknown error has occured\n");
      }
   }else{
      // TODO: Specific errors dependant on status

      printf("./StegTool image.png input.txt output.png\n");
      printf("./StegTool -d image.png input.txt \n");
   }

   free(args);

   return 0;
}