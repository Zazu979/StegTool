/*
 * @Author: Zazu
 * @Date:   2018-12-22 11:51:58
 * @Git:    https://github.com/Zazu979
 * @Last Modified by:   Zazu
 * @Last Modified time: 2018-12-22 11:51:58
*/


#include <stdio.h>
#include <stdlib.h>
#include <argp.h>
#include <stdbool.h>

#include <readArgs.h>

#define VERSION_MAJOR  "0"
#define VERSION_MINOR  "1"
#define VERSION_STRING "Stegtool "

#define VERSION VERSION_STRING VERSION_MAJOR "." VERSION_MINOR 

const char *argp_program_version = VERSION;
const char *argp_program_bug_address =
  "<jonathon.winter979@gmail.com>";

const char doc[] = "Steganography Tool to hide and remove files in images";

static struct argp_option options[] = {
  {"input",    'i', "IMAGE", 0, "Image to be read" },
  {"file",     'f', "FILE",  0, "File to be hidden" },
  {"output",   'o', "FILE/IMAGE",  0, "Output file, image or any file" },
  {"verbose",  'v', 0,       0, "Produce verbose output" },
  {"desteg",   'd', 0,       0, "Retrieve file from a image" },
  { 0 }
};

int parse_opt (int key, char *arg, struct argp_state *state)
{
   /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
   Arguments* args = (Arguments*)state->input;

   switch (key){
      case 'i':
         args->imageFile = arg;
         break;
      case 'f':
         args->inputFile = arg;
         break;
      case 'o':
         args->outputFile = arg;
         break;
      case 'd':
         args->type = DESTROY_STEG;
         break;
      case 'v':
         args->verbose = true;
         break;
      default:
         return ARGP_ERR_UNKNOWN;
   }
   return 0;
}


Arguments* createArgs(){
   Arguments* args = (Arguments*)malloc(sizeof(Arguments));
   
   args->imageFile = NULL;
   args->inputFile = NULL;
   args->outputFile = NULL;
   args->verbose = false;
   args->type = CREATE_STEG;

   args->status = VALID;

   return args;

}

void checkArgs(Arguments* args){

   // There must be an image file to be read
   if(args->imageFile == NULL){
      args->status = NO_IMAGE_FILE;
   }
   // There must be an output file, whether it be an image or text file
   else if(args->outputFile == NULL){
      args->status = NO_OUTPUT_FILE;
   }
   // If you are create a steg then their must also be in input file.
   else if(args->type == CREATE_STEG){
      if(args->inputFile == NULL){
         args->status = NO_INPUT_FILE;
      }
   }

   // TODO Add validation on impossible combinations

}

Arguments* readArgs(int argc, char** argv){

   Arguments* args = createArgs();
   static struct argp argp = { options, parse_opt, 0, doc };

   argp_parse(&argp, argc, argv, 0, 0, args);

   checkArgs(args);

   return args;

}
