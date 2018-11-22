/*
* @Author: zazu
* @Date:   2018-11-22 10:37:39
* @Last Modified by:   zazu
* @Last Modified time: 2018-11-22 14:51:49
*/

#include <stdio.h>
#include <stdlib.h>
#include <argp.h>
#include <stdbool.h>

#include <readArgs.h>

#define VERSION_MAJOR  "0"
#define VERSION_MINOR  "0"
#define VERSION_STRING "Stegtool "


#define VERSION VERSION_STRING VERSION_MAJOR "." VERSION_MINOR 

const char *argp_program_version = VERSION;
const char *argp_program_bug_address =
  "<jonathon.winter979@gmail.com>";

static char doc[] = "Steganography Tool to hide and remove files in images";

static struct argp_option options[] = {
  {"input",    'i', "IMAGE", 0, "Image to be read" },
  {"file",     'f', "FILE",  0, "File to be hidden" },
  {"output",   'o', "FILE",  0, "Output file, image or txt file" },
  {"verbose",  'v', 0,       0, "Produce verbose output" },
  {"desteg",   'd', 0,       0, "Retrieve file from a image" },
  { 0 }
};

int parse_opt (int key, char *arg, struct argp_state *state)
{
   /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
   Arguments* args = state->input;

   switch (key)
   {
      case 'i':
         args->imageFile = arg;
         break;
      case 'f':
         args->inputFile = arg;
         break;
      case 'o':
         args->outputFile = arg;
         break;
      case 't':
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

   return args;

}

static struct argp argp = { options, parse_opt, 0, doc };

void readArgs(int argc, char** argv){

   Arguments* args = createArgs();

   argp_parse (&argp, argc, argv, 0, 0, args);



   printf("imageFile: %s\ninputFile: %s\noutputFile: %s\nverbose: %s\ntype: %s\n",
         args->imageFile,
         args->inputFile,
         args->outputFile,
         args->verbose == true ? "TRUE" : "FALSE",
         args->type == CREATE_STEG ? "create" : "destroy");
}
