/*
 * @Author: Zazu
 * @Date:   2018-12-22 11:51:55
 * @Git:    https://github.com/Zazu979
 * @Last Modified by: Zazu
 * @Last Modified time: 2019-01-26 18:54:00
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

#include <fileType.h>
// #include <encryption.h>

int main(int argc, char **argv){

   Arguments* args = readArgs(argc, argv);

   if(args->status == VALID){

      setVerbose(args->verbose);

      if(args->type == CREATE_STEG){
         createSteganography(args->imageFile, args->dataFile, args->outputFile, args->bitSize);
      }else if(args->type == DESTROY_STEG){
         destroySteganography(args->imageFile, args->outputFile);
      }else{
         printf("Unknown error has occured\n");
      }
   }else{
      // TODO: Specific errors dependant on status

      printf("./StegTool -i input.png -f data.txt -o output.png\n");
      printf("./StegTool -d -i input.png -o data.txt \n");
   }

   free(args);

   return 0;
}